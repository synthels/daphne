#ifndef __LIB__CONFIG_H__
#define __LIB__CONFIG_H__

#include <stddef.h>
#include <stdbool.h>
#include <lib/part.h>

extern bool config_ready;

struct menu_entry {
    char name[64];
    struct menu_entry *parent;
    struct menu_entry *sub;
    bool expanded;
    char *body;
    struct menu_entry *next;
};

extern struct menu_entry *menu_tree;

int init_config_disk(struct volume *part);
int init_config_pxe(void);
int init_config(size_t config_size);
bool config_get_entry_name(char *ret, size_t index, size_t limit);
char *config_get_entry(size_t *size, size_t index);
char *config_get_value(const char *config, size_t index, const char *key);

#endif
