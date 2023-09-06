#include <rcl/rcl.h> //accesso funzionalità di ROS 2 basilari
#include <rcl/error_handling.h> //gestione errori applicazioni
#include <rcl/node.h> //creazione e gestione nodi
#include <workspace_ros/message_for_motor.h> //creare messaggio per motore


//funzione che gestisce i messaggi della seriale
//ConstPtr è uno shared pointer
string serial_message(const msg_ser::String::ConstPtr& msg)
{
  
  if(strcmp(msg->bodym, "error")!=0)
  {
    return msg;
  }
  else
  {
    return "failure";
  }
  
}


int main()
{
  //SetUp preliminari
  rclc_support_t support;
  rclc_support_init(&support, argc, argv, &allocator);

 //inizializzazione del nodo motre
  rclc_node_init_default(&my_node, "motor_node", "", &support);
  
}



