/* Zach Wibbenmeyer
 * Professor Norman
 * CS232 - Project 4
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/syscall.h>
#include <semaphore.h>

// baker is either baking or is at the cash register
sem_t bakerSem;

// only 5 people allowed in the store at a time
sem_t storeSem;

//only admits one customer at a time
sem_t custSem;

// 10 threads used for customers
pthread_t customerThread[10];

int customers = 0;
int customerWaiting = -1;
int checkouts = 0;
int breadBaked = 0;
int breadAvailable = 0;


/*
 * getCustomers() - returns the number of customers
 * @param: None
 * @return: an int
 */
int getCustomers() {
    pthread_t id = pthread_self();
    int i;
    for (i = 0; i < 10; i++) {
        if (pthread_equal(id, customerThread[i])) {
            return i;
        }
    }
    return -1;
}

/*
 * *bakerCheckout() - allows the customer to checkout and makes sure the baker is only baking
 *						one loaf of bread
 * @param: *arg (type -> void)
 * @return: Nothing
 */
void *bakerCheckout(void *arg) {
    while (checkouts < 10) {
        while (customerWaiting == -1 ) {
                sleep(0.1);
        }
        printf("Customer [%d] is waiting to checkout\n", customerWaiting);
        sem_wait(&bakerSem);
        sleep(1);
        printf("The baker has printed a receipt for customer [%d]\n", customerWaiting);
        customerWaiting = -1;
        checkouts++;
        sem_post(&bakerSem);
    }
}

/*
 * *customerActions() - main actions the customer performs
 * @param: *arg (type -> void)
 * @return: Nothing
 */
void *customerActions(void *arg)
{
    printf("Customer [%d] is trying to enter the store\n", getCustomers());
    sem_wait(&storeSem);
    printf("Customer [%d] has entered the store\n", getCustomers());

    sem_wait(&custSem);

    // request the bread
    printf("Customer [%d] is waiting for some bread\n", getCustomers());
    while(breadAvailable == 0) {
      	sleep(0.1); //sleep, check again
    }

    breadAvailable--;
    printf("Customer [%d] has received the bread\n", getCustomers());
    sleep(2);
    
    // the customer pays
    int waitNum = checkouts + 1;
    printf("Customer [%d] has paid\n", getCustomers());
    customerWaiting = getCustomers();

    while (customerWaiting != -1) {
        sleep(0.1);
    }
    printf("Customer [%d] has taken the receipt and left\n", getCustomers());
    customers--;
    sem_post(&custSem);
    sem_post(&storeSem);
    return NULL;
}

/*
 * *bakeBread() - Process for the baker to bake bread
 * @param: None
 * @return: Nothing
 */
void *bakeBread() {
    printf("The baker is ready\n");
    while (breadBaked != 10) {
        sem_wait(&bakerSem);
        breadAvailable++;
	      breadBaked++;
        printf("The baker has baked a single loaf of bread\n");
        sem_post(&bakerSem);
        sleep(1);
    }
    printf("The baker is done baking loaves of bread.\n");
}

/* Initialize semaphores */
void initialize() {
    sem_init(&custSem, 0, 1);
    sem_init(&bakerSem, 0, 1);
    sem_init(&storeSem, 0, 5);
}

// main program
int main()
{
    initialize();
    printf("---Creating customers---\n");
    pthread_t bakeBreadId;
    pthread_t checkoutId;
    pthread_create(&bakeBreadId, NULL, bakeBread, NULL);
    pthread_create(&checkoutId, NULL, bakerCheckout, NULL);
    int i;
    for (i = 0; i < 10; i++) {
        customers++;
        pthread_create(&customerThread[i], NULL, customerActions, NULL);
    }
    pthread_exit(NULL);
    printf("---All customers have left the store---\n");
    exit(0);
}