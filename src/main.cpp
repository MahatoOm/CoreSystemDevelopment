#include <iostream>
#include <string>
#include <cctype>
#include <fstream> 

using namespace std;

int  main(){

    // Reading files
    std::ifstream file("data/resources.txt");

    if (!file.is_open()){
        cerr<< "Couild not open file\n";
        return 1;
    }
    string line;
    while (getline(file, line)){
        cout << line << '\n';
    }
    file.close();

    
    int choice;
    bool a = true;
    // Defining optionanity    
    while (a){
    cout << " ===== Campus Resource Reservation System ===== " << endl;
    cout << " 1. View Resources \n 2. Create Reservation \n 3. Cancel Reservation \n 4. View Waiting Lists \n 5. Undo Cancellation \n 6. Search Reservations \n 7. Sort Resources \n 8. Generate Report \n 9. Exit" << endl;
    cout << "Enter Choice: ";

    
    cin >> choice;

    if (choice == 1){

    }
    else if(choice == 2){

    }
    else if(choice == 3){

    }else if(choice == 4){
        
    }else if(choice == 5){
        
    }else if(choice == 6){
        
    }else if(choice == 7){
        
    }else if(choice == 8){
        
    }else if(choice == 9){
        break;
        
    }else {
        cout << "Invalid Output"<< endl; 
    }
    cout <<"\n\n"<< endl;

}

return 0;

} 