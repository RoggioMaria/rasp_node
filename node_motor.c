//Nodo per motore 
#include <rcl/rcl.h> //accesso funzionalità di ROS 2 basilari
#include <rcl/error_handling.h> //gestione errori applicazioni
#include <rcl/node.h> //creazione e gestione nodi
#include "std_msgs/msg/string.h"  
#include <stdio.h>
#include <string>


//funzione che gestisce i messaggi della seriale
//ConstPtr è uno shared pointer


std_msgs__msg__String last_msg; //l'ultimo messaggio ricevuto
void MotorCommand(const void *msgin)
{
  const std_msgs__msg__String *msg = (const std_msgs__msg__String *)msgin;
  last_msg = *msg; // Sovrascrivi l'ultimo messaggio con il nuovo messaggio ricevuto
  if(strcmp(last_msg->data.data), 'right'){
    printf("DESTRA");
  }
  else if(strcmp(last_msg->data.data), 'left'){
     printf("SINISTRA\n");
  }
  else if(strcmp(last_msg->data.data), 'on'){
     printf("SU\n");
  }
  else if(strcmp(last_msg->data.data), 'down')
  {
     printf("GIU\n");
  }
  else{
     printf("error topic!\n");
  }

}
int main()
{
  //parte uguale
  rcl_init(argc, argv); //comunicazione
  rcl_node_t node = rcl_get_zero_initialized_node(); //inizzializzazione
  rcl_subscription_t subscription = rcl_get_zero_initialized_subscription(); //variabile con valori 0

  rcl_node_options_t node_options = rcl_node_get_default_options(); //configurazione di default per il nodo
  rcl_ret_t ret = rcl_node_init(&node, "node_motor", "", &node_options); //creazione nodo "node_sensor"

  //sottoscrizione al topic "Motor_commands" del nodo "node_sensor"
  ret = rcl_subscription_init(&subscription, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String), "Motor_commands", NULL);

  rcl_allocator_t allocator = rcl_get_default_allocator(); //gestisce lae allocazioni di memoria in maniera sicura all'interno di Ros2
  rcl_wait_set_t wait_set = rcl_get_zero_initialized_wait_set();  //set vuoto di descrittori
  ret = rcl_wait_set_init(&wait_set, 1, 0, 0, 0, 0, allocator)); //settiamo quello che vogliamo monitoriare in oridine timer, pub, sub, guardie e servizi
  
  ret = rcl_wait_set_clear(&wait_set); //cancella il set definito prima rimuove tutti gli oggeti in attesa
  ret = rcl_wait_set_add_subscription(&wait_set, &subscription, NULL);  //aggiunge la sottoscrizione al set di attesa

  //start 
   while (1) {
    ret = rcl_wait(&wait_set, RCL_MS_TO_NS(1000)); // risultato dell'attesa dopo 1 sec
     
    if (ret == RCL_RET_TIMEOUT) { //è passato 1 sec ma non ci sono stati messaggi
      printf("No messages received.\n");
    } 
    else if (ret != RCL_RET_OK) {
      fprintf(stderr, "Error in waiting: %s\n", rcl_get_error_string().str);
      return 1;
    } 
    else {
       //gestisci comandi motore
      string msg="";
      MotorCommand(msg);
    }
    
  
    }

  rcl_subscription_fini(&subscription, &node);
  rcl_node_fini(&node);
  rcl_shutdown();
  return 0;




  
  }
  





