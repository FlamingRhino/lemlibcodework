#include "subsyttem.cpp"





inline void colortask(){

  bool onred = true;
  int count = 0;
  bool ison = true;
  int onoff = 0;
    while (true) {

      if(ison == true){
      if(onred == true){
       if (Color.get_hue() >= 0 and Color.get_hue() <= 3 or Color.get_hue() >= 257 and Color.get_hue() <= 260){
          Sorter.extend();
         pros::delay(500);
         Sorter.retract();
        }

      }else{

       if (Color.get_hue() >= 215 and Color.get_hue() <= 225 ){
          Sorter.extend();
         pros::delay(500);
          Sorter.retract();
         }


      }
      }

      if(master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
        if(onred == true){
          onred = false;
        }else{
          onred = true;
        }
      }
      

      if(master.get_digital(DIGITAL_RIGHT)){
        if(ison){
          ison = false;
        }else{
          ison = true;
        }
      }

      


     if (!(count % 6)) {
       //Only print every 50ms, the controller text update rate is slow
       if(onoff == 0){
        if(onred){
          master.print(1, 0, "on BLUE");
        }else{
          master.print(1, 0, "on RED ");
        }

        onoff = 1;
       }else{
          if(ison){
          master.print(1, 10, "ON  ");
        }else{
          master.print(1, 10, "OFF");
        }
          onoff = 0;

       }

    }
    count++;



    




        pros::delay(20);
        
  } 

  master.print(1, 0, "on red? =AAAAAA: %f");
}








