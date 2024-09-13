#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//This code is made by Abacan, Lorenz Althea 

class Product{
	private:
		string productID, productName;
		double price;
		int quantity;
	
	public:
		Product(){
			//default
		}
		
		Product(string productID, string productName, double price){
			this->productID = productID;
			this->productName = productName;
			this->price = price;
		}
		
		void setID(string id){
			this->productID = id;
		}
		
		void setName(string name){
			this->productName = name;
		}
		
		void setPrice(double price){
			this->price = price;
		}
		
		double getPrice(){
			return price;
		}
		
		string getName(){
			return productName;
		}
		
		void printProduct(){
			cout<<fixed
				<<setw(15)<<productID
				<<setw(15)<<productName
				<<setw(15)<<setprecision(2)<<price<<endl;
		}
		
		void printProductQ(){
			cout<<fixed
				<<setw(15)<<productID
				<<setw(15)<<productName
				<<setw(15)<<setprecision(2)<<price
				<<setw(15)<<getQuan()<<endl;
		}
		
		string getID(){
			return productID;
		}
		
		void setQuantity(int quant){
			this->quantity = quant;
		}
		
		int getQuan(){
			return quantity;
		}
};

class ShoppingCart : public Product{
	private:
		Product list[20];
		int maxIndex;
	public:
		ShoppingCart(){
			//Default constructor
		}
		
		void setListValues(string productID, string productName, double price, int index){
			list[index].setID(productID);
			list[index].setName(productName);
			list[index].setPrice(price);
		}
		
		void printProductList(int index){
			for(int x = 0; x < index; x++){
				list[x].printProduct();
			}
		}
		
		void printProductListQ(int index){
			for(int x = 0; x < index; x++){
				if(list[x].getQuan() > 0)
					list[x].printProductQ();
			}
		}
		
		double getTotal(int max){
			double total = 0;
			for(int x = 0; x < max; x++){
				total = total + (list[x].getPrice()*list[x].getQuan());
			}
		}
		
		void setMax(int val){
			this->maxIndex = val;
		}
		
		int getMax(){
			return maxIndex;
		}
		
		int findTarget(string target){
			int loc = -1;
			for(int x = 0; x < maxIndex; x++){
				if(target == list[x].getID())
					loc = x;
			}
			
			return loc;
		}
		
		Product returnProduct(int index){
			return list[index];
		}
		
		void replaceValues(Product copy, int paste, int quant){
			list[paste] = copy;
			list[paste].setQuantity(quant);
		}
		
};

//Once you pick an order it will bring to the Shoppingcart
class Order: public ShoppingCart{
	private:
	//array for the shopingcart in how much it can hold
		ShoppingCart cart[20];
};

int main(){
	ShoppingCart menu;
	menu.setMax(6);
	
	Order listing[10];
	//Product options to pick
	menu.setListValues("ABC", "Donut", 100.52, 0);
	menu.setListValues("DEF", "Cupcake", 600.54, 1);
	menu.setListValues("HIJ", "Siomai Rice", 100.52, 2);
	menu.setListValues("KLM", "Extra Gravy", 600.54, 3);
	menu.setListValues("NOP", "Prayd Tsiken", 9.11, 4);
	menu.setListValues("QRS", "Bagels", 55.52, 5);

	bool repeat = true;
	int select, ctr = 0, orders = -1;
	//This the Menu and inputs of your choices
	do{
		int choice;
		cout<<"==================== Main Menu ===================="<<endl
			<<"1. View Products"<<endl
			<<"2. View Shopping Cart"<<endl
			<<"3. View Orders"<<endl
			<<"4. Add Order"<<endl
			<<"5. Remove Order"<<endl
			<<"6. Finalize Order"<<endl
			<<"7. Exit"<<endl
			<<"Your Choice: ";
		cin>> choice;
		
		switch(choice){
			case 1:
				cout<<endl<<"================== View Products =================="<<endl;
				cout<<fixed
					<<setw(15)<<"Product ID"
					<<setw(15)<<"Name"
					<<setw(15)<<"Price"<<endl;
					
					menu.printProductList(6);
					cout<<endl;
					
				break;
				
			case 2:
				cout<<endl<<"================== Shopping Cart =================="<<endl;
					if(0 < listing[ctr].getMax()){
						cout<<fixed
						<<setw(15)<<"Product ID"
						<<setw(15)<<"Name"
						<<setw(15)<<"Price"
						<<setw(15)<<"Quantity"<<endl;
						
					listing[ctr].printProductListQ(listing[ctr].getMax());
				}
				else{
					cout<<"Your cart is empty."<<endl;
				}
				
				cout<<endl;
				break;
				
			case 3:
				cout<<endl<<"=================== View Orders ==================="<<endl;
				if(ctr > 0){
					for(int x = 0; x < ctr; x++){
						cout<<"Order ID: "<<x+1<<endl
							<<"Total Amount: "<<fixed<<setprecision(2)<<listing[x].getTotal(listing[x].getMax())<<endl
							<<"Order Details: "<<endl;
							cout<<fixed
								<<setw(15)<<"Product ID"
								<<setw(15)<<"Name"
								<<setw(15)<<"Price"
								<<setw(15)<<"Quantity"
								<<endl;
						for(int y = 0; y < listing[ctr-1].getMax(); y++){
							listing[y].printProductListQ(listing[y].getMax());
						}
						cout<<endl;
					}
				}
				else{
					cout<<"Your order is empty."<<endl;
				}
				
				cout<<endl;
				break;
			case 4:
				{
					cout<<endl<<"==================== Add Order ===================="<<endl;
					bool correct = false;
					orders++;
					string tempID;
					bool addItem = true;
					do{
							cout<<"Enter ID of product to add: ";
							cin>>tempID;
							
							for(int x = 0; x < 6; x++){
								if(menu.findTarget(tempID) > -1)
									correct = true;
								}
								
							if(correct == true){
								int tempQ;
								cout<<"Enter Quantity: ";
								cin>>tempQ;
								
								listing[ctr].replaceValues(menu.returnProduct(menu.findTarget(tempID)), listing[ctr].getMax(), tempQ);
								listing[ctr].setMax(listing[ctr].getMax()+1);
								cout<<"Item added to cart"<<endl;
							}
								
							else
								cout<<"Item not found"<<endl;
							
							cout<<endl;
							correct = false;
							int conf;
							do{
								cout<<"Do you want to add another item?"<<endl
									<<"1. Yes"<<endl
									<<"2. No"<<endl
									<<"Your Choice: ";
								cin>>conf;
								
								switch(conf){
									case 1:
										addItem = true;
										cout<<endl;
										break;
									case 2:
										addItem = false;
										cout<<endl;
										break;
									default:
										cout<<"Invalid input... try choosing from the selection above."<<endl;
								}
							}while(conf <= 0 || conf >= 3);
						
					}while(addItem == true);
					break;
				}
			case 5:
				{
					cout<<endl<<"================== Remove Orders =================="<<endl;
					bool loop = true;
					int remove;
					do{
						cout<<"Enter Order# to remove: ";
						cin>>remove;
						
						if(remove > 0 && remove < ctr+1){
							cout<<"Removing order#"<<remove<<"..."<<endl;
							for(int x = remove-1; x < ctr; x++){
								listing[x] = listing[x+1];
							}
							ctr--;
						}
							
						else
							cout<<"Order #"<<remove<<" does not exist in the list..."<<endl;
						
						
						cout<<"Do you want to continue removing orders?"<<endl
							<<"1. Yes"<<endl
							<<"2. No"<<endl
							<<"Your Choice: ";
						cin>>remove;
						
						
						bool valid = false;
						do{
							if(remove == 1){
								loop = true;
								valid = true;								
							}
							else if(remove == 2){
								loop = false;
								valid = true;
							}
							else{
								cout<<"Invalid response, try answering with the numbers shown in the options..."<<endl;
								loop = true;
							}							
						}while(valid == false);
																
					}while(loop == true);
					break;
				}
			case 6:
				cout<<endl<<"================= Finalize Orders ================="<<endl;
				cout<<"Order #"<<ctr+1<<" is finalized... you can no longer edit its content."<<endl;
				ctr++;
				cout<<endl;
				break;
			
			case 7:
				{
					int confirm;
					do{
						cout<<endl<<"================ Confirm Leave ================"<<endl;
						cout<<"Do you want to leave the program?"<<endl
							<<"1. Yes"<<endl
							<<"2. No"<<endl
							<<"Your Choice: ";
						cin>>confirm;
					}while(confirm > 2 || confirm < 1);
					
					if(confirm == 2){
						cout<<"Returning to program"<<endl<<endl;
					}
						
					else{
						cout<<"Leaving program..."<<endl<<endl;
						repeat = false;
					}	
					break;
				}
			default:
				cout<<"Invalid input... try entering a number from the presented menu."<<endl<<endl;
				break;
		}	
	}while(repeat == true);
	

	return 0;
}

//Yuriko 4ever
