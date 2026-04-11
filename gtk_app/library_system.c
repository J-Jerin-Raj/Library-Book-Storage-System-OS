#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BLOCKS 100
#define ROWS 10
#define COLS 10

typedef struct {
    char name[50];
    int size;
    int blocks[MAX_BLOCKS]; 
    int method;             // 0: Contig, 1: Linked, 2: Indexed
    int index_block;        
    GdkRGBA color;
} Book;

// Global State
Book library[50];
int book_count = 0;
int disk[MAX_BLOCKS]; 
int searched_book_id = -1; 

GtkWidget *block_containers[MAX_BLOCKS];
GtkWidget *entry_name, *entry_size, *combo_method, *search_entry, *status_label;

// Helper: Random Color
GdkRGBA get_random_color() {
    GdkRGBA color;
    color.red = (double)(rand() % 100) / 200.0 + 0.2;
    color.green = (double)(rand() % 100) / 200.0 + 0.2;
    color.blue = (double)(rand() % 100) / 200.0 + 0.2;
    color.alpha = 1.0;
    return color;
}

// Refresh UI Grid
void refresh_disk_map() {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        gtk_widget_override_background_color(block_containers[i], GTK_STATE_FLAG_NORMAL, &(GdkRGBA){0.9, 0.9, 0.9, 1.0});
    }

    for (int i = 0; i < book_count; i++) {
        for (int j = 0; j < library[i].size; j++) {
            int b_idx = library[i].blocks[j];
            if (i == searched_book_id) {
                gtk_widget_override_background_color(block_containers[b_idx], GTK_STATE_FLAG_NORMAL, &(GdkRGBA){1.0, 1.0, 0.0, 1.0}); 
            } else {
                if (library[i].method == 2 && b_idx == library[i].index_block) {
                    gtk_widget_override_background_color(block_containers[b_idx], GTK_STATE_FLAG_NORMAL, &(GdkRGBA){0.1, 0.1, 0.1, 1.0}); // Index is Black
                } else {
                    gtk_widget_override_background_color(block_containers[b_idx], GTK_STATE_FLAG_NORMAL, &library[i].color);
                }
            }
        }
    }
}

// Logic: Allocation
void on_add_clicked(GtkButton *b, gpointer user_data) {
    const char *name = gtk_entry_get_text(GTK_ENTRY(entry_name));
    int size = atoi(gtk_entry_get_text(GTK_ENTRY(entry_size)));
    int method = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_method));
    searched_book_id = -1; 

    if (size <= 0 || strlen(name) == 0) {
        gtk_label_set_text(GTK_LABEL(status_label), "Status: Invalid Input");
        return;
    }

    Book nb;
    strcpy(nb.name, name);
    nb.size = size;
    nb.method = method;
    nb.color = get_random_color();
    nb.index_block = -1;

    if (method == 0) { // Contiguous
        int start = -1;
        for (int i = 0; i <= MAX_BLOCKS - size; i++) {
            int ok = 1;
            for (int j = 0; j < size; j++) if (disk[i+j]) { ok = 0; break; }
            if (ok) { start = i; break; }
        }
        if (start != -1) {
            for (int i = 0; i < size; i++) { disk[start+i] = 1; nb.blocks[i] = start+i; }
            library[book_count++] = nb;
            gtk_label_set_text(GTK_LABEL(status_label), "Status: Contiguous Success");
        } else gtk_label_set_text(GTK_LABEL(status_label), "Status: No Contiguous Space");
    }
    else if (method == 1) { // Linked
        int found = 0;
        for (int i = 0; i < MAX_BLOCKS && found < size; i++) if (!disk[i]) found++;
        if (found >= size) {
            int k = 0;
            for (int i = 0; i < MAX_BLOCKS && k < size; i++) {
                if (!disk[i]) { disk[i] = 1; nb.blocks[k++] = i; }
            }
            library[book_count++] = nb;
            gtk_label_set_text(GTK_LABEL(status_label), "Status: Linked Success");
        } else gtk_label_set_text(GTK_LABEL(status_label), "Status: Disk Full");
    }
    else if (method == 2) { // Indexed
        int found = 0;
        for (int i = 0; i < MAX_BLOCKS && found < size + 1; i++) if (!disk[i]) found++;
        if (found >= size + 1) {
            int k = 0;
            for (int i = 0; i < MAX_BLOCKS && k < size + 1; i++) {
                if (!disk[i]) {
                    disk[i] = 1;
                    if (k == 0) nb.index_block = i; 
                    nb.blocks[k++] = i;
                }
            }
            nb.size = size + 1; 
            library[book_count++] = nb;
            gtk_label_set_text(GTK_LABEL(status_label), "Status: Indexed Success (Black=Index)");
        } else gtk_label_set_text(GTK_LABEL(status_label), "Status: No space for Index block");
    }
    refresh_disk_map();
}

void on_search_clicked(GtkButton *b, gpointer user_data) {
    const char *query = gtk_entry_get_text(GTK_ENTRY(search_entry));
    for (int i = 0; i < book_count; i++) {
        if (strcasecmp(library[i].name, query) == 0) {
            searched_book_id = i;
            gtk_label_set_text(GTK_LABEL(status_label), "Found: Highlighted in Yellow");
            refresh_disk_map();
            return;
        }
    }
    gtk_label_set_text(GTK_LABEL(status_label), "Book not found.");
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "OS Library Storage System");
    gtk_window_set_default_size(GTK_WINDOW(window), 900, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // Sidebar
    GtkWidget *vbox_side = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(vbox_side), 15);
    gtk_box_pack_start(GTK_BOX(hbox), vbox_side, FALSE, FALSE, 0);

    GtkWidget *lbl_title = gtk_label_new("<b>BOOK DETAILS</b>");
    gtk_label_set_use_markup(GTK_LABEL(lbl_title), TRUE);
    gtk_box_pack_start(GTK_BOX(vbox_side), lbl_title, FALSE, FALSE, 5);

    entry_name = gtk_entry_new(); gtk_entry_set_placeholder_text(GTK_ENTRY(entry_name), "Book Name");
    gtk_box_pack_start(GTK_BOX(vbox_side), entry_name, FALSE, FALSE, 0);

    entry_size = gtk_entry_new(); gtk_entry_set_placeholder_text(GTK_ENTRY(entry_size), "Blocks (Size)");
    gtk_box_pack_start(GTK_BOX(vbox_side), entry_size, FALSE, FALSE, 0);

    combo_method = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_method), "Contiguous");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_method), "Linked");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_method), "Indexed");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_method), 0);
    gtk_box_pack_start(GTK_BOX(vbox_side), combo_method, FALSE, FALSE, 0);

    GtkWidget *btn_add = gtk_button_new_with_label("Store Book");
    g_signal_connect(btn_add, "clicked", G_CALLBACK(on_add_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox_side), btn_add, FALSE, FALSE, 10);

    search_entry = gtk_entry_new(); gtk_entry_set_placeholder_text(GTK_ENTRY(search_entry), "Search Name...");
    gtk_box_pack_start(GTK_BOX(vbox_side), search_entry, FALSE, FALSE, 20);

    GtkWidget *btn_search = gtk_button_new_with_label("Search & Highlight");
    g_signal_connect(btn_search, "clicked", G_CALLBACK(on_search_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox_side), btn_search, FALSE, FALSE, 5);

    status_label = gtk_label_new("Ready");
    gtk_box_pack_end(GTK_BOX(vbox_side), status_label, FALSE, FALSE, 10);

    // Grid Visualizer
    GtkWidget *vbox_grid = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(hbox), vbox_grid, TRUE, TRUE, 10);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    
    for (int r = 0; r < ROWS; r++) {
        char rack_text[20]; sprintf(rack_text, "Rack %d →", r + 1);
        gtk_grid_attach(GTK_GRID(grid), gtk_label_new(rack_text), 0, r, 1, 1);
        for (int c = 0; c < COLS; c++) {
            int idx = r * COLS + c;
            block_containers[idx] = gtk_event_box_new();
            gtk_widget_set_size_request(block_containers[idx], 40, 40);
            char num[5]; sprintf(num, "%d", idx);
            gtk_container_add(GTK_CONTAINER(block_containers[idx]), gtk_label_new(num));
            gtk_grid_attach(GTK_GRID(grid), block_containers[idx], c + 1, r, 1, 1);
            disk[idx] = 0;
        }
    }
    gtk_box_pack_start(GTK_BOX(vbox_grid), gtk_label_new("STORAGE BLOCK MAP"), FALSE, FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox_grid), grid, FALSE, FALSE, 0);

    refresh_disk_map();
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}