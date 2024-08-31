#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

// User class to store user information
class User {
private:
    string username;
public:
    User(string name){
        this->username = name;
    }
    string getUsername(){
        return username; 
    }
};

// Message struct to represent a message between users
struct Message {
    string sender;
    string recipient;
    string content;
    Message(string from, string to, string text){
        this->sender = from;
        this->recipient = to;
        this->content = text;
    }
};

// SocialNetwork class to manage users, friendships, groups, and messages
class SocialNetwork {
private:
    unordered_map<string, User> users;
    unordered_map<string, unordered_set<string>> friendships;
    unordered_map<string, unordered_set<string>> groups;
    unordered_map<string, queue<Message>> messageQueue;

public:
    // Add a new user to the network
    void addUser(string username) {
        users.emplace(username, User(username));
        friendships.emplace(username, unordered_set<string>());
    }

    // Make two users friends
    void addFriendship(string user1, string user2) {
        friendships[user1].insert(user2);
        friendships[user2].insert(user1);
    }

    // Create a new group and add users to it
    void createGroup(string groupName, vector<string> groupMembers) {
        groups.emplace(groupName, unordered_set<string>());
        for (string& member : groupMembers) {
            groups[groupName].insert(member);
        }
    }

    // Remove a friendship between two users
    void removeFriendship(string user1, string user2) {
        friendships[user1].erase(user2);
        friendships[user2].erase(user1);
    }

    // Remove a user from a group
    void removeFromGroup(string username, string groupName) {
        groups[groupName].erase(username);
    }

    // Send a message from one user to another
    void sendMessage(string sender, string recipient, string message) {
        messageQueue[recipient].emplace(sender, recipient, message);
    }

    // Print all messages for a user (dequeues and prints)
    void printMessages(string username) {
        if (messageQueue.find(username) != messageQueue.end()) {
            cout << "Messages for " << username << ":" << endl;
            while (!messageQueue[username].empty()) {
                Message msg = messageQueue[username].front();
                cout << "[" << msg.sender << " -> " << msg.recipient << "]: " << msg.content << endl;
                messageQueue[username].pop();
            }
        } else {
            cout << "No messages for " << username << endl;
        }
    }

    // Print all friendships in the network
    void printFriendships() {
        cout << "Friendships:" << endl;
        for (auto& pair : friendships) {
            string user = pair.first;
            cout << user << " has friends: ";
            for (string friendName : pair.second) {
                cout << friendName << " ";
            }
            cout << endl;
        }
    }

    // Print all groups and their members
    void printGroups() {
        cout << "Groups:" << endl;
        for (auto& pair : groups) {
            string groupName = pair.first;
            cout << groupName << " includes: ";
            for (string member : pair.second) {
                cout << member << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    SocialNetwork network;

    // Adding users
    network.addUser("Alice");
    network.addUser("Bob");
    network.addUser("Charlie");

    // Making friends
    network.addFriendship("Alice", "Bob");
    network.addFriendship("Bob", "Charlie");

    // Creating groups
    network.createGroup("Group1", {"Alice", "Bob"});
    network.createGroup("Group2", {"Charlie"});

    // Sending messages
    network.sendMessage("Alice", "Bob", "Hey Bob, how are you?");
    network.sendMessage("Charlie", "Alice", "Hi Alice, what's up?");

    // Printing initial state
    network.printFriendships();
    network.printGroups();

    // Printing messages for Alice
    network.printMessages("Alice");

    // Removing a friendship
    network.removeFriendship("Alice", "Bob");

    // Removing from a group
    network.removeFromGroup("Bob", "Group1");

    // Printing state after modifications
    network.printFriendships();
    network.printGroups();

    // Printing messages for Bob (should be empty)
    network.printMessages("Bob");

    return 0;
}
