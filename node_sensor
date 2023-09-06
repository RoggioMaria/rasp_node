#include <stdio.h>
#include "rcl/rcl.h"
#include "rcl/error_handling.h"
#include "std_msgs/msg/string.h"

int main(int argc, char **argv)
{
          /*Questa parte è uguale per tutti i nodi tranne per la dichiarazione pub 
                    e sub che dipende dal tipo di nodo*/
  rcl_init(argc, argv); //comunicazione ROS2

//inizializzazione e creazione nodo publisher per il nodo che pubblica
  rcl_node_t node = rcl_get_zero_initialized_node(); 
  rcl_publisher_t publisher = rcl_get_zero_initialized_publisher(); //restituisce una variabile inizializzata con tutti valori a 0

//configurazione nodo con valori di default e creazione del nodo "node_sensor"
  rcl_node_options_t node_options = rcl_node_get_default_options();
  rcl_ret_t ret = rcl_node_init(&node, "node_sensor", "", &node_options); //controllo errore mancante
//definisce il publisher sensor e caricherà i messaggi nel topic "Motor_commands"
ret = rcl_publisher_init(&publisher, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String), "Motor_commands", NULL); //controllo errore mancante

  std_msgs__msg__String msg; //dichiara il message
  std_msgs__msg__String__init(&msg); //inizializza il messaggio
  msg.data.data = "on"; //il messaggio sarà

  while (1) {
    ret = rcl_publish(&publisher, &msg, NULL); //pubblica il messaggio
    printf("Published: %s\n", msg.data.data);
    rcl_sleep_ms(1000); // Publish every 1 second //ogni secondo
  }

  rcl_publisher_fini(&publisher, &node); //dealloca le risorse del pub
  rcl_node_fini(&node); //dealloca le risorse legate al nodo
  rcl_shutdown();// rilascia le risorse di ROS2
  return 0;
}

}
