/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * @author Dwei
 */

#include "queue.h"
#include "harness.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL)
        return;
    list_ele_t *prev;
    while (q->head != NULL) {
        // save the current head
        prev = q->head;
        // move q->head to the next
        q->head = q->head->next;
        // free saved node: prev value
        free(prev->value);
        // free saved node itself
        free(prev);
    }
    free(q);
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {
    if (q == NULL || s == NULL)
        return false;
    list_ele_t *newhead = malloc(sizeof(list_ele_t));
    if (newhead == NULL)
        return false;
    char *copy = malloc(strlen(s) + 1);
    if (copy == NULL) {
        free(newhead); // this is so tricky, to remember to free newhead
        return false;
    }
    strcpy(copy, s);

    newhead->next = q->head;
    newhead->value = copy;
    q->head = newhead;
    q->size++;
    if (q->tail == NULL)
        q->tail = q->head; // when it is a new Queue
    return true;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    if (q == NULL || s == NULL)
        return false;
    list_ele_t *newtail = malloc(sizeof(list_ele_t));
    if (newtail == NULL)
        return false;
    char *copy = malloc(strlen(s) + 1);
    if (copy == NULL) {
        free(newtail);
        return false;
    }
    strcpy(copy, s);
    newtail->next = NULL;
    newtail->value = copy;

    if (q->tail == NULL) { // empty queue
        q->head = newtail;
        q->tail = newtail;
    } else {
        q->tail->next = newtail;
        q->tail = newtail;
    }
    q->size++;
    return true;
}

/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    if (q == NULL || q->size == 0)
        return false;
    // copy string
    if (buf != NULL && bufsize > 0) {
        size_t i;
        for (i = 0; i < bufsize - 1 && *(q->head->value + i) != '\0'; i++) {
            *(buf + i) = *(q->head->value + i);
        }
        *(buf + i) = '\0';
    }
    list_ele_t *temp = q->head;
    // now remove head
    q->head = q->head->next;
    // check if new head is null, this is the special case where the old q
    // ony has one element, tail and head both point to the same element
    if (q->head == NULL)
        q->tail = NULL;
    // free old head
    free(temp->value);
    free(temp);
    q->size--;
    return true;
}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL)
        return 0;
    return q->size;
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    if (q == NULL || q->size == 0)
        return;
    list_ele_t *prev = NULL;
    list_ele_t *curr = q->head;
    // update head and tail pointer
    q->head = q->tail;
    q->tail = curr;
    while (curr != NULL) {
        // save next
        list_ele_t *temp = curr->next;
        // reverse pointer
        curr->next = prev;
        // update prev to curr, curr to next
        prev = curr;
        curr = temp;
    }
}
