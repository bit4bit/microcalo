/**
 *Se pasan funcionalidades a script guile
 *para facilitar la creacion del video juego :)
 */

#include "script.h"
#include "compositor.h"
#include "escenario_intro.h"
#include <iostream>
#include <string>
#include <libguile.h>



void script_cargar_escenario_intro(EscenarioIntro *escenario_intro, const char *scm_var) {
   SCM comandos = scm_variable_ref(scm_c_lookup(scm_var));
 
   while(SCM_FALSEP(scm_null_p(comandos))) {
     SCM scm_value = SCM_CAR(comandos);
     SCM scm_tipo = SCM_CAR(scm_value);
     SCM scm_data = SCM_CAR(SCM_CDR(scm_value));

     
     char * tipo = scm_to_locale_string(scm_symbol_to_string(scm_tipo));
     char * data = scm_to_locale_string(scm_data);

     EscenarioIntroComando *comando = new EscenarioIntroComando(std::string(tipo),std::string(data));
     escenario_intro->agregarComando(comando);
   
     scm_dynwind_free(tipo); scm_dynwind_free(data);
     comandos = SCM_CDR(comandos);
   }
}

void* iniciar_script(void *data) {
  const char *script_ruta = (char*) data;
  std::cout << "scripting ruta:" << script_ruta << std::endl;
  /*declaracion a guile*/

  #include "script.x"
  scm_c_primitive_load(script_ruta);
}

