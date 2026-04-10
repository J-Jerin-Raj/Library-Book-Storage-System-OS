#include <gtk/gtk.h>
#include <stdio.h>

#define memsize 50

int memory[memsize] = {0};
GtkWidget *output;

// helper to show output
void show_msg(char *msg) {
    gtk_label_set_text(GTK_LABEL(output), msg);
}

// display memory
void disp() {
    static char buffer[2000];
    char temp[10];

    buffer[0] = '\0';

    for (int i = 0; i < memsize; i++) {
        sprintf(temp, "%d ", memory[i]);
        strcat(buffer, temp);
    }

    gtk_label_set_text(GTK_LABEL(output), buffer);
}

// CONTIGUOUS (GUI version)
void conti(GtkButton *btn, gpointer data) {
    int start = 2, size = 3; // demo fixed (you can add input fields later)

    for (int i = start; i < start + size; i++) {
        if (memory[i] != 0) {
            show_msg("Contiguous Allocation Failed");
            return;
        }
    }

    for (int i = start; i < start + size; i++) {
        memory[i] = 1;
    }

    show_msg("Contiguous Allocation Done");
}

// LINKED (GUI version)
void link(GtkButton *btn, gpointer data) {
    int blocks[] = {5, 10, 15};
    int size = 3;

    for (int i = 0; i < size; i++) {
        if (memory[blocks[i]] != 0) {
            show_msg("Linked Allocation Failed");
            return;
        }
    }

    for (int i = 0; i < size; i++) {
        memory[blocks[i]] = 1;
    }

    show_msg("Linked Allocation Done");
}

// INDEXED (GUI version)
void indexA(GtkButton *btn, gpointer data) {
    int index = 0;
    int blocks[] = {1, 2, 3};
    int size = 3;

    if (memory[index] != 0) {
        show_msg("Index Block Already Used");
        return;
    }

    memory[index] = 1;

    for (int i = 0; i < size; i++) {
        memory[blocks[i]] = 1;
    }

    show_msg("Indexed Allocation Done [0 -> 1,2,3]");
}

// UI setup
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Library Storage System");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), box);

    GtkWidget *btn1 = gtk_button_new_with_label("Contiguous Allocation");
    GtkWidget *btn2 = gtk_button_new_with_label("Linked Allocation");
    GtkWidget *btn3 = gtk_button_new_with_label("Indexed Allocation");
    GtkWidget *btn4 = gtk_button_new_with_label("Display Memory");

    output = gtk_label_new("Output will appear here");

    gtk_box_pack_start(GTK_BOX(box), btn1, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), btn2, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), btn3, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), btn4, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), output, TRUE, TRUE, 5);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(btn1, "clicked", G_CALLBACK(conti), NULL);
    g_signal_connect(btn2, "clicked", G_CALLBACK(link), NULL);
    g_signal_connect(btn3, "clicked", G_CALLBACK(indexA), NULL);
    g_signal_connect(btn4, "clicked", G_CALLBACK(disp), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}