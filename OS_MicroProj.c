#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define memsize 50

int memory[memsize] = {0};

// Widgets
GtkWidget *entry_id;
GtkWidget *entry_start;
GtkWidget *entry_size;
GtkWidget *entry_blocks;
GtkWidget *output;

// show output
void show(const char *msg) {
    gtk_label_set_text(GTK_LABEL(output), msg);
}

// display memory
void display_mem(GtkButton *btn, gpointer data) {
    static char buffer[2000];
    char temp[20];

    buffer[0] = '\0';

    for (int i = 0; i < memsize; i++) {
        sprintf(temp, "%d ", memory[i]);
        strcat(buffer, temp);
    }

    gtk_label_set_text(GTK_LABEL(output), buffer);
}

// CONTIGUOUS
void conti(GtkButton *btn, gpointer data) {
    int id = atoi(gtk_entry_get_text(GTK_ENTRY(entry_id)));
    int start = atoi(gtk_entry_get_text(GTK_ENTRY(entry_start)));
    int size = atoi(gtk_entry_get_text(GTK_ENTRY(entry_size)));

    if (start < 0 || start + size > memsize) {
        show("Invalid range");
        return;
    }

    for (int i = start; i < start + size; i++) {
        if (memory[i] != 0) {
            show("Contiguous Allocation Failed");
            return;
        }
    }

    for (int i = start; i < start + size; i++) {
        memory[i] = id;
    }

    show("Contiguous Allocation Successful");
}

// LINKED
void link_alloc(GtkButton *btn, gpointer data) {
    int id = atoi(gtk_entry_get_text(GTK_ENTRY(entry_id)));
    char input[200];
    strcpy(input, gtk_entry_get_text(GTK_ENTRY(entry_blocks)));

    int blocks[memsize], size = 0;

    char *token = strtok(input, ",");

    while (token != NULL) {
        blocks[size++] = atoi(token);
        token = strtok(NULL, ",");
    }

    for (int i = 0; i < size; i++) {
        if (blocks[i] < 0 || blocks[i] >= memsize || memory[blocks[i]] != 0) {
            show("Linked Allocation Failed");
            return;
        }
    }

    for (int i = 0; i < size; i++) {
        memory[blocks[i]] = id;
    }

    show("Linked Allocation Successful");
}

// INDEXED
void indexA(GtkButton *btn, gpointer data) {
    int id = atoi(gtk_entry_get_text(GTK_ENTRY(entry_id)));
    int index = atoi(gtk_entry_get_text(GTK_ENTRY(entry_start)));
    char input[200];

    strcpy(input, gtk_entry_get_text(GTK_ENTRY(entry_blocks)));

    int blocks[memsize], size = 0;

    char *token = strtok(input, ",");

    if (memory[index] != 0) {
        show("Index block already used");
        return;
    }

    memory[index] = id;

    while (token != NULL) {
        blocks[size++] = atoi(token);
        token = strtok(NULL, ",");
    }

    for (int i = 0; i < size; i++) {
        if (memory[blocks[i]] != 0) {
            show("Indexed Allocation Failed");
            return;
        }
    }

    for (int i = 0; i < size; i++) {
        memory[blocks[i]] = id;
    }

    show("[Index -> Blocks] Allocation Done");
}

// MAIN UI
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Library Storage System");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 500);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), box);

    entry_id = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_id), "Book ID");

    entry_start = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_start), "Start / Index Block");

    entry_size = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_size), "Size (for contiguous)");

    entry_blocks = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_blocks), "Blocks (comma separated e.g. 1,2,3)");

    GtkWidget *btn1 = gtk_button_new_with_label("Contiguous Allocation");
    GtkWidget *btn2 = gtk_button_new_with_label("Linked Allocation");
    GtkWidget *btn3 = gtk_button_new_with_label("Indexed Allocation");
    GtkWidget *btn4 = gtk_button_new_with_label("Display Memory");

    output = gtk_label_new("Output appears here");

    gtk_box_pack_start(GTK_BOX(box), entry_id, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), entry_start, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), entry_size, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), entry_blocks, FALSE, FALSE, 5);

    gtk_box_pack_start(GTK_BOX(box), btn1, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), btn2, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), btn3, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), btn4, FALSE, FALSE, 5);

    gtk_box_pack_start(GTK_BOX(box), output, TRUE, TRUE, 5);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(btn1, "clicked", G_CALLBACK(conti), NULL);
    g_signal_connect(btn2, "clicked", G_CALLBACK(link_alloc), NULL);
    g_signal_connect(btn3, "clicked", G_CALLBACK(indexA), NULL);
    g_signal_connect(btn4, "clicked", G_CALLBACK(display_mem), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}