/*
 * Author: neurd
 * Date: 16th November 2026
 *
 * MSList: a Mini and Simple List Implementation
 *
 * This implementation of dynamic lists are with circular xor linked lists.
 * We used malloc for this one, so expect to use heap allocation for this
 * implementation
 */

#ifndef MSLIST_H
#define MSLIST_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef MSH_INLINE
#if defined(__cplusplus)
#define MSH_INLINE inline
#elif defined(__GNUC__) || defined(__clang__)
#define MSH_INLINE static inline __attribute__((unused))
#else
#define MSH_INLINE static inline
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ListNode list_node_t;

struct ListNode {
  void *data;
  list_node_t *link;
};

MSH_INLINE list_node_t *new_node(void *data) {
  list_node_t *node = (list_node_t *)malloc(sizeof(list_node_t));
  if (node == NULL) {
    return NULL;
  }

  node->data = data;
  node->link = NULL;

  return node;
}

typedef struct LinkedList linked_list_t;

struct LinkedList {
  list_node_t *head;
  list_node_t *tail;
  size_t size;
};

MSH_INLINE list_node_t *XOR(list_node_t *a, list_node_t *b) {
  return (list_node_t *)((uintptr_t)(a) ^ (uintptr_t)(b));
}

MSH_INLINE void _mslist_insert_between(list_node_t *prev, list_node_t *curr,
                                       list_node_t *node) {
  node->link = XOR(prev, curr);
  prev->link = XOR(XOR(prev->link, curr), node);
  curr->link = XOR(XOR(curr->link, prev), node);
}

MSH_INLINE linked_list_t *linked_list_init(void) {
  linked_list_t *new_list = (linked_list_t *)malloc(sizeof(linked_list_t));
  if (new_list == NULL) {
    return NULL;
  }

  new_list->head = NULL;
  new_list->tail = NULL;
  new_list->size = 0;

  return new_list;
}

MSH_INLINE void linked_list_push_front(linked_list_t *list, void *data) {
  if (list == NULL) {
    return;
  }

  list_node_t *node = new_node(data);
  if (node == NULL) {
    return;
  }

  if (list->size == 0) {
    list->head = node;
    list->tail = node;
  } else {
    _mslist_insert_between(list->tail, list->head, node);
    list->head = node;
  }
  list->size++;
}

MSH_INLINE void linked_list_push_back(linked_list_t *list, void *data) {
  if (list == NULL) {
    return;
  }

  list_node_t *node = new_node(data);
  if (node == NULL) {
    return;
  }

  if (list->size == 0) {
    list->head = node;
    list->tail = node;
  } else {
    _mslist_insert_between(list->tail, list->head, node);
    list->tail = node;
  }
  list->size++;
}

MSH_INLINE void linked_list_insert_at(linked_list_t *list, void *data,
                                      size_t idx) {
  if (list == NULL || idx > list->size) {
    return;
  }

  if (idx == 0) {
    linked_list_push_front(list, data);
    return;
  }

  if (idx == list->size) {
    linked_list_push_back(list, data);
    return;
  }

  list_node_t *node = new_node(data);
  if (node == NULL) {
    return;
  }

  list_node_t *prev = list->tail;
  list_node_t *curr = list->head;
  for (size_t i = 0; i < idx; i++) {
    list_node_t *next = XOR(curr->link, prev);
    prev = curr;
    curr = next;
  }

  _mslist_insert_between(prev, curr, node);
  list->size++;
}

MSH_INLINE void *linked_list_pop_front(linked_list_t *list) {
  if (list == NULL || list->size == 0) {
    return NULL;
  }

  list_node_t *curr = list->head;
  void *data = curr->data;

  if (list->size == 1) {
    list->head = NULL;
    list->tail = NULL;
  } else {
    list_node_t *tail = list->tail;
    list_node_t *next = XOR(curr->link, tail);

    next->link = XOR(XOR(next->link, curr), tail);
    tail->link = XOR(XOR(tail->link, curr), next);
    list->head = next;
  }

  list->size--;
  free(curr);
  return data;
}

MSH_INLINE void *linked_list_pop_back(linked_list_t *list) {
  if (list == NULL || list->size == 0) {
    return NULL;
  }

  list_node_t *curr = list->tail;
  void *data = curr->data;

  if (list->size == 1) {
    list->head = NULL;
    list->tail = NULL;
  } else {
    list_node_t *head = list->head;
    list_node_t *prev = XOR(curr->link, head);

    prev->link = XOR(XOR(prev->link, curr), head);
    head->link = XOR(XOR(head->link, curr), prev);
    list->tail = prev;
  }

  list->size--;
  free(curr);
  return data;
}

MSH_INLINE void linked_list_delete(linked_list_t *list, void *data) {
  if (list == NULL || list->size == 0) {
    return;
  }

  list_node_t *prev = list->tail;
  list_node_t *curr = list->head;

  for (size_t i = 0; i < list->size; i++) {
    if (curr->data == data) {
      if (curr == list->head) {
        linked_list_pop_front(list);
      } else if (curr == list->tail) {
        linked_list_pop_back(list);
      } else {
        list_node_t *next = XOR(curr->link, prev);
        prev->link = XOR(XOR(prev->link, curr), next);
        next->link = XOR(XOR(next->link, curr), prev);
        free(curr);
        list->size--;
      }
      return;
    }

    list_node_t *next = XOR(curr->link, prev);
    prev = curr;
    curr = next;
  }
}

MSH_INLINE void linked_list_destroy(linked_list_t *list) {
  if (list == NULL) {
    return;
  }

  list_node_t *curr = list->head;
  list_node_t *prev = list->tail;

  for (size_t i = 0; i < list->size; i++) {
    list_node_t *next = XOR(curr->link, prev);
    prev = curr;
    free(curr);
    curr = next;
  }

  free(list);
}

#ifdef __cplusplus
}
#endif

#endif // MSLIST_H
