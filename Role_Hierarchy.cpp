#include<bits/stdc++.h>
using namespace std;
void solve();
int main (){solve();return 0;}
//                      TEMPLATE
//                        ENDS
//                        HERE


class Role {
public:
	string role_name;
	map<string,Role*> children_roles;
	Role* parent;
	vector<string>users;
};
map<string,Role*> directory;
map<string,string> userToRole;
bool checker(string role_name)
{
	auto rolefind = directory.find(role_name);


	if(rolefind!=directory.end())
	{
		return true;

	}
	else 
	{
		cout << role_name << endl;
		cout << "Could not find the entered role in the hierarchy.\nPlease ensure that you have entered the Role name\n" << endl;
		return false;
	}
}
Role* get_root_role()
{
	string rr;
	cout << "\nEnter the root role: ";
	getline(cin, rr);
	cout << endl;

	// creating a new instance
	Role* root_role = new Role();

	root_role->role_name = rr;
	root_role->parent = NULL;

	return root_role;
}
void add_sub_role()
{

	string sub_role_name,reporting_role_name;
	cout << "\nEnter sub role name : ";
	getline(cin,sub_role_name);
	cout << "\nEnter reporting to role name : ";
	getline(cin,reporting_role_name);
	
	//debug(sub_role_name);
	//debug(reporting_role_name);
	
	Role* new_role = new Role();
	
	// first check whether duplicates
	// now lets not do that , but in later corrections
	new_role->role_name = sub_role_name;


	if(!checker(reporting_role_name)) return;
	auto parentPair = directory.find(reporting_role_name);


	Role* parent = parentPair->second;
	new_role->parent = parent;
	
	
	
	// Reflect the update in the parent node as well
	parent->children_roles.insert({sub_role_name,new_role});
	// add new_role in our map directory
	directory.insert({sub_role_name,new_role});

}

void display(Role* root_role,bool flag)
{
	
	queue<Role*> queue_node;

	queue_node.push(root_role);
	while(queue_node.size()!=0)
	{
		Role* temp = queue_node.front();

		cout << temp->role_name << " ";
		queue_node.pop();

		for(auto children:temp->children_roles)
			queue_node.push(children.second);
	}
}
void delete_role(Role* root_role)
{
	string role_to_be_deleted,role_to_be_transferred;
	cout << "\nEnter the Role Tobe Deleted : ";
	getline(cin,role_to_be_deleted);
	cout << "\nEnter the Role Tobe Transferred : ";
	getline(cin,role_to_be_transferred);

	if(!checker(role_to_be_deleted)) return;
	if(!checker(role_to_be_transferred)) return;

	// 1. get the node to be deleted and transferred
	// 2. transfer the children from the node to be deleted to node to be transferred
	// 3. get the parent nodes of both roles
	// 4. remove these nodes as the child from old parent nodes
	// 5. set the parent of the new node = parent of the deleted node 
	// 6. add this new node as the child as the parent of the deleted node
	// 7. copy all the users from delete to be node to the transfer to be node
	// 8. delete the node from directory well
	// 9. free the node

	// 1.
	auto pair1 = directory.find(role_to_be_deleted);
	auto pair2 = directory.find(role_to_be_transferred);
	Role* deleteToBe = pair1->second;
	Role* transferToBe = pair2->second;
	//2. no need delete children as they will be freed from existence after deleting parent node and they are just 
	// 	 pointers not the real roles
	for(auto item:deleteToBe->children_roles)
	{if(item.second != transferToBe)
		transferToBe->children_roles.insert(item);
	}
	//3. 
	Role* parentOfDeleteToBe = deleteToBe->parent;
	Role* parentOfTransferToBe = transferToBe->parent;

	//4.
	auto it = parentOfDeleteToBe->children_roles.find(role_to_be_deleted);
	parentOfDeleteToBe->children_roles.erase(it);

	it = parentOfTransferToBe->children_roles.find(role_to_be_transferred);
	cout << parentOfTransferToBe->role_name << endl;
	parentOfTransferToBe->children_roles.erase(it);

	//5.
	transferToBe->parent = parentOfDeleteToBe;
	//6.
	 parentOfDeleteToBe->children_roles.insert({ role_to_be_transferred,transferToBe});

	//7.
	 for(auto user:deleteToBe->users)
	 {
	 	transferToBe->users.push_back(user);
	 }

	 //8.
	directory.erase(role_to_be_deleted);
	//8.
	delete(deleteToBe);
}
void add_users()
{

	string user_name,role_name;
	cout << "\nEnter User Name : ";
	getline(cin,user_name);
	cout << "\nEnter Role : ";
	getline(cin,role_name);

	if(!checker(role_name)) return;

	auto it = directory.find(role_name);

	Role* roleNode = it->second;

	userToRole.insert({user_name,role_name});
	roleNode->users.push_back(user_name);
}
void displayUsers2(Role* root_role)
{
	
	queue<Role*> queue_node;

	queue_node.push(root_role);
	while(queue_node.size()!=0)
	{
		Role* temp = queue_node.front();

		
		int n = 0;
		for(auto it:temp->users)
		{
			cout << it ;


			if(n!=temp->users.size())
						cout << " , ";
		}

		//cout << temp->role_name << " - ";
		queue_node.pop();

		for(auto children:temp->children_roles)
			queue_node.push(children.second);
	}
}

void displayUsersAndSubRoles(Role* root_role)
{
	
	queue<Role*> queue_node;

	queue_node.push(root_role);
	
	while(queue_node.size()!=0)
	{
		Role* temp = queue_node.front();


		int n = 0;

		for(auto it:temp->users)
		{
			cout << it;
			
			if(n++!=temp->users.size())
						cout << " - ";
		}
		
		

		queue_node.pop();

		for(auto children:temp->children_roles)
		{	
			displayUsers2(children.second);
			queue_node.push(children.second);
		}

		if(temp->users.size() !=0)	cout  << endl;
	

	}

}
void displayUsers(Role* root_role)
{
	
	queue<Role*> queue_node;

	queue_node.push(root_role);
	while(queue_node.size()!=0)
	{
		Role* temp = queue_node.front();

		
		int i =0;
		int n = temp->users.size();
		for(auto it:temp->users)
		{
			cout << it;
			if(++i!=n) cout << ",";
		}

		if(n) cout << " - ";
		else{
			cout << "NA" << " - ";
		}
		cout << temp->role_name << endl ;
		queue_node.pop();

		for(auto children:temp->children_roles)
			queue_node.push(children.second);
	}
}

void delete_users(Role* root_role)
{	
	string user_name_tobe_deleted;
	cout << "\nEnter the Username to be delete : ";
	getline(cin,user_name_tobe_deleted);

	// 1. get the role of the user through the user-role mapping
	// 2. get the address of role node throught the directory
	// 3. get to the vector throught, find and delete the user
	// 4. thats it

	// 1.
	//cout << user_name_tobe_deleted << endl;
	string role_name = userToRole[user_name_tobe_deleted];

	// 2.
	if(!checker(role_name)) return;
	auto it = directory.find(role_name);
	//cout << role_name << user_name_tobe_deleted <<  endl;
	Role* temp = it->second;		 
	//cout << temp->users[0] << endl;

	auto iter = std::find(temp->users.begin(), temp->users.end(), user_name_tobe_deleted);
    temp->users.erase(iter);




}
void solve ()
{

	// root role
	Role* root_role = new Role();
	// to get instant address of a role node by string
	root_role = get_root_role();
	directory.insert({root_role->role_name,root_role});


	for(;;)
	{	string choice;
		
		// choice 1 - add sub role
		cout << "\nOperations:\n\t1.Add Sub Role.\n\t2.Display\n\t3.Delete Role\n\t4.Add users\n\t5.Display Users\n\t6.Display User an Subusers\n\t7.Delete Users\n\t9.Quit";
		cout << "\n\nOperation to be performed: ";
		getline(cin,choice);
	cout << endl << endl;

		if(choice == "1")
		{
			add_sub_role();
			
		}
		else if(choice == "2")
		{
			display(root_role,true);
		}
		else if(choice == "3")
		{
			delete_role(root_role);
		}
		else if(choice == "4")
		{
			add_users();
		}
		else if(choice == "5")
		{
			displayUsers(root_role);
		}
		else if(choice == "6")
		{
			displayUsersAndSubRoles(root_role);
			//couldnt get it working
		}
		else if(choice == "7")
		{
			// not working properly
			delete_users(root_role);
		}
		else if(choice == "9") return;
	cout << endl << endl;

	}
	


	
	return;
}





