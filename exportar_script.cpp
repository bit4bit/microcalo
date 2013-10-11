#include "exportar_script.h"

mrb_data_type escenario_menu_type = {"EscenarioMenu", exportar_script_free_null};
mrb_data_type rwidget_type = {"RWidget", exportar_script_free};
mrb_data_type graficador_type = {"Graficador", exportar_script_free};
mrb_data_type escenario_guion_type = {"EscenarioGuion", exportar_script_free_null};
mrb_data_type juego_type = {"Juego", exportar_script_free_null};
RClass* c_escenario_menu;
RClass* c_rwidget;
RClass* c_graficador;
RClass* c_escenario_guion;
RClass* c_juego;
void exportar_script_free(mrb_state *mrb, void *d) { delete d;}
void exportar_script_free_null(mrb_state *mrb, void* data) {}
