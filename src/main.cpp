#include <iostream>
#include <string>
#include <cctype>

#include "ReservationManager.h"



using namespace std;

int  main(){

    ReservationManager manager;

    manager.loadResources();
    manager.loadReservations();

    int choice;
    bool a = true;
    // Defining optionanity    
    while (a){
    cout << " ===== Campus Resource Reservation System ===== " << endl;
    cout << " 1. View Resources \n 2. Create Reservation \n 3. Cancel Reservation \n 4. View Waiting Lists \n 5. Undo Cancellation \n 6. Undo Reservation \n 7. Search Reservations \n 8. Sort Resources \n 9. Generate Report \n 0. Exit" << endl;
    cout << "Enter Choice: ";

    
    cin >> choice;

    if (choice == 1){
        manager.displayResources();
        
    }
    else if(choice == 2){
        manager.createReservation();
    }
    else if(choice == 3){
        manager.cancelReservation();

    }else if(choice == 4){
        manager.displayReservations();

    }else if(choice == 5){
        manager.displayWaitingList();

    }else if(choice == 6){
        manager.undoCancellation();
        
    }else if(choice == 7){
        manager.searchReservation();
    }else if(choice == 8){
        manager.displayCancellationHistory();
        
    }else if(choice == 9){
        manager.addToWaitingList();
        break;
    }else if(choice == 0){

        cout << "Exiting Program ... \n" ;
        a = false;
        break;
       
    }else {
        cout << "Invalid Output"<< endl; 
    }
    cout <<"\n\n"<< endl;

}

return 0;

} 


