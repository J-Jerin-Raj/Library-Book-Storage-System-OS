#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

#define memsize 50

int memory[memsize] = {0};

GtkWidget *output;

// Show message
void show_msg(const char *msg) {
    gtk_label_set_text(GTK_LABEL(output), msg);
}

// Display memory
void disp(GtkButton *btn, gpointer data) {
    static char buffer[2000];
    char temp[20];

    buffer[0] = '\0';

    for (int i = 0; i < memsize; i++) {
        sprintf(temp, "%d ", memory[i]);
        strcat(buffer, temp);
    }

    gtk_label_set_text(GTK_LABEL(output), buffer);
}

// Check duplicate book ID
int exists(int id) {
    for (int i = 0; i < memsize; i++) {
        if (memory[i] == id)
            return 1;
    }
    return 0;
}

// Contiguous Allocation
void conti(GtkButton *btn, gpointer data) {
    int start = 2, size = 3, id = 101;

    if (exists(id)) {
        show_msg("Book ID already exists");
        return;
    }

    if (start < 0 || start + size > memsize) {
        show_msg("Invalid range");
        return;
    }

    for (int i = start; i < start + size; i++) {
        if (memory[i] != 0) {
            show_msg("Contiguous Allocation Failed");
            return;
        }
    }

    for (int i = start; i < start + size; i++) {
        memory[i] = id;
    }

    show_msg("Contiguous Allocation Successful");
}

// LINKED ALLOCATION (RENAMED FIXED FUNCTION)
void link_alloc(GtkButton *btn, gpointer data) {
    int id = 202;
    int blocks[] = {5, 10, 15};
    int size = 3;

    if (exists(id)) {
        show_msg("Book ID already exists");
        return;
    }

    for (int i = 0; i < size; i++) {
        if (blocks[i] < 0 || blocks[i] >= memsize) {
            show_msg("Invalid index");
            return;
        }

        if (memory[blocks[i]] != 0) {
            show_msg("Linked Allocation Failed");
            return;
        }
    }

    for (int i = 0; i < size; i++) {
        memory[blocks[i]] = id;
    }

    show_msg("Linked Allocation Successful");
}

// INDEXED ALLOCATION
void indexA(GtkButton *btn, gpointer data) {
    int id = 303;
    int index = 0;
    int blocks[] = {1, 2, 3};
    int size = 3;

    if (exists(id)) {
        show_msg("Book ID already exists");
        return;
    }

    if (memory[index] != 0) {
        show_msg("Index block already used");
        return;
    }

    memory[index] = id;

    for (int i = 0; i < size; i++) {
        memory[blocks[i]] = id;
    }

    show_msg("[0 -> 1,2,3] Indexed Allocation Done");
}

// GTK UI
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Library Storage System");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), box);

    GtkWidget *btn1 = gtk_button_new_with_label("Contiguous Allocation");
    GtkWidget *btn2 = gtk_button_new_with_label("Linked Allocation");
    GtkWidget *btn3 = gtk_button_new_with_label("Indexed Allocation");
    GtkWidget *btn4 = gtk_button_new_with_label("Display Memory");

    output = gtk_label_new("Output here");

    gtk_box_pack_start(GTK_BOX(box), btn1, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), btn2, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), btn3, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), btn4, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), output, TRUE, TRUE, 5);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(btn1, "clicked", G_CALLBACK(conti), NULL);
    g_signal_connect(btn2, "clicked", G_CALLBACK(link_alloc), NULL);  // FIXED HERE
    g_signal_connect(btn3, "clicked", G_CALLBACK(indexA), NULL);
    g_signal_connect(btn4, "clicked", G_CALLBACK(disp), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}