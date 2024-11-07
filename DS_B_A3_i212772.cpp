#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#define MAX_GAMES 50  // Maximum number of games a player can have

// Helper functions for manual parsing
long long stringToLongLong(const char* str) {
    long long result = 0;
    int i = 0;
    while (str[i] != '\0') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result;
}

double stringToDouble(const char* str) {
    double result = 0.0;
    double fraction = 1.0;
    bool decimalPointSeen = false;
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '.') {
            decimalPointSeen = true;
        } else {
            if (decimalPointSeen) {
                fraction *= 0.1;
                result += (str[i] - '0') * fraction;
            } else {
                result = result * 10 + (str[i] - '0');
            }
        }
        i++;
    }
    return result;
}

class Game {
public:
    long long gameID;
    char gameName[50];
    char developer[50];
    char publisher[50];
    double rating;
    int numDownloads;

    Game(long long id, const char* name, const char* dev, const char* pub, double rate, int downloads)
        : gameID(id), rating(rate), numDownloads(downloads) {
        strcpy(gameName, name);
        strcpy(developer, dev);
        strcpy(publisher, pub);
    }
};

class Player {
public:
    long long playerID;
    char playerName[50];
    char phoneNumber[20];
    char email[50];
    char password[50];
    long long primaryGameID;
    double rating;
    int numGames;
    long long gameIDs[MAX_GAMES];
    double gameRatings[MAX_GAMES];

    Player(long long id, const char* name, const char* phone, const char* mail, const char* pass, long long primaryGame, double rate)
        : playerID(id), primaryGameID(primaryGame), rating(rate), numGames(0) {
        strcpy(playerName, name);
        strcpy(phoneNumber, phone);
        strcpy(email, mail);
        strcpy(password, pass);
    }

    void addGame(long long gameID, double gameRating) {
        if (numGames < MAX_GAMES) {
            gameIDs[numGames] = gameID;
            gameRatings[numGames] = gameRating;
            numGames++;
        }
    }
};

class TreeNode {
public:
    Player* player;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Player* p) : player(p), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, Player* player) {
        if (!node) return new TreeNode(player);
        if (player->playerID < node->player->playerID)
            node->left = insert(node->left, player);
        else if (player->playerID > node->player->playerID)
            node->right = insert(node->right, player);
        else
            std::cout << "Duplicate Player ID. Insertion ignored." << std::endl;
        return node;
    }

    TreeNode* search(TreeNode* node, long long playerID) {
        if (!node || node->player->playerID == playerID) return node;
        if (playerID < node->player->playerID)
            return search(node->left, playerID);
        return search(node->right, playerID);
    }

    TreeNode* deleteNode(TreeNode* node, long long playerID) {
        if (!node) return nullptr;
        if (playerID < node->player->playerID)
            node->left = deleteNode(node->left, playerID);
        else if (playerID > node->player->playerID)
            node->right = deleteNode(node->right, playerID);
        else {
            if (!node->left) {
                TreeNode* rightChild = node->right;
                delete node->player;
                delete node;
                return rightChild;
            }
            if (!node->right) {
                TreeNode* leftChild = node->left;
                delete node->player;
                delete node;
                return leftChild;
            }
            TreeNode* minNode = findMin(node->right);
            node->player = minNode->player;
            node->right = deleteNode(node->right, minNode->player->playerID);
        }
        return node;
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->left) node = node->left;
        return node;
    }

    void preorderSave(TreeNode* node, std::ofstream& file) {
        if (!node) return;
        Player* p = node->player;
        file << p->playerID << "," << p->playerName << "," << p->phoneNumber << "," << p->email << ","
             << p->password << "," << p->primaryGameID << "," << p->rating << "\n";
        preorderSave(node->left, file);
        preorderSave(node->right, file);
    }

    void displayLayers(TreeNode* node, int currentLayer, int maxLayers) {
        if (!node || currentLayer > maxLayers) return;
        std::cout << "Player ID: " << node->player->playerID << ", Name: " << node->player->playerName << "\n";
        displayLayers(node->left, currentLayer + 1, maxLayers);
        displayLayers(node->right, currentLayer + 1, maxLayers);
    }

    int getLayer(TreeNode* node, long long playerID, int depth) {
        if (!node) return -1;
        if (node->player->playerID == playerID) return depth;
        int leftDepth = getLayer(node->left, playerID, depth + 1);
        if (leftDepth != -1) return leftDepth;
        return getLayer(node->right, playerID, depth + 1);
    }

    bool showPath(TreeNode* node, long long playerID) {
        if (!node) return false;
        std::cout << node->player->playerID << " ";
        if (node->player->playerID == playerID) return true;
        if (showPath(node->left, playerID) || showPath(node->right, playerID)) return true;
        return false;
    }

    void topNPlayers(TreeNode* node, int& n) {
        if (!node || n <= 0) return;
        topNPlayers(node->right, n);
        if (n > 0) {
            std::cout << "Player ID: " << node->player->playerID << ", Name: " << node->player->playerName
                      << ", Games Played: " << node->player->numGames << "\n";
            n--;
        }
        topNPlayers(node->left, n);
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        deleteTree(root);
    }

    void insert(Player* player) {
        root = insert(root, player);
    }

    Player* search(long long playerID) {
        TreeNode* node = search(root, playerID);
        return node ? node->player : nullptr;
    }

    void deletePlayer(long long playerID) {
        root = deleteNode(root, playerID);
    }

    void saveToFile(const char* filename) {
        std::ofstream file(filename);
        preorderSave(root, file);
    }

    void showNLayers(int layers) {
        displayLayers(root, 1, layers);
    }

    int getLayerNumber(long long playerID) {
        return getLayer(root, playerID, 1);
    }

    void showPathToPlayer(long long playerID) {
        if (!showPath(root, playerID)) {
            std::cout << "Player not found.\n";
        }
    }

    void displayTopNPlayers(int n) {
        std::cout << "Top " << n << " players with most games:\n";
        topNPlayers(root, n);
    }

private:
    void deleteTree(TreeNode* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node->player;
        delete node;
    }
};


class GameList {
public:
    Game** games;
    int capacity;
    int size;

    GameList(int cap) : capacity(cap), size(0) {
        games = new Game*[capacity];
    }

    ~GameList() {
        for (int i = 0; i < size; i++) {
            delete games[i];
        }
        delete[] games;
    }

    void addGame(Game* game) {
        if (size < capacity) {
            games[size++] = game;
        }
    }

    Game* searchGame(long long gameID) {
        for (int i = 0; i < size; i++) {
            if (games[i]->gameID == gameID) return games[i];
        }
        return nullptr;
    }

    void displayAllGames() {
        for (int i = 0; i < size; i++) {
            std::cout << "Game ID: " << games[i]->gameID << ", Name: " << games[i]->gameName
                      << ", Developer: " << games[i]->developer << ", Publisher: " << games[i]->publisher
                      << ", Rating: " << games[i]->rating << ", Downloads: " << games[i]->numDownloads << "\n";
        }
    }
};

void loadPlayers(BST& bst, const char* filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        char* token = strtok(&line[0], ",");
        if (!token) continue;
        long long playerID = stringToLongLong(token);

        token = strtok(nullptr, ",");
        if (!token) continue;
        char playerName[50];
        strcpy(playerName, token);

        token = strtok(nullptr, ",");
        if (!token) continue;
        char phoneNumber[20];
        strcpy(phoneNumber, token);

        token = strtok(nullptr, ",");
        if (!token) continue;
        char email[50];
        strcpy(email, token);

        token = strtok(nullptr, ",");
        if (!token) continue;
        char password[50];
        strcpy(password, token);

        token = strtok(nullptr, ",");
        if (!token) continue;
        long long primaryGameID = stringToLongLong(token);

        token = strtok(nullptr, ",");
        if (!token) continue;
        double rating = stringToDouble(token);

        Player* player = new Player(playerID, playerName, phoneNumber, email, password, primaryGameID, rating);

        while ((token = strtok(nullptr, ",")) != nullptr) {
            long long gameID = stringToLongLong(token);
            token = strtok(nullptr, ",");
            if (!token) break;
            double gameRating = stringToDouble(token);
            player->addGame(gameID, gameRating);
        }

        bst.insert(player);
    }
}

void loadGames(GameList& gameList, const char* filename) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        char* token = strtok(&line[0], ",");
        if (!token) continue;
        long long gameID = stringToLongLong(token);

        token = strtok(nullptr, ",");
        if (!token) continue;
        char gameName[50];
        strcpy(gameName, token);

        token = strtok(nullptr, ",");
        if (!token) continue;
        char developer[50];
        strcpy(developer, token);

        token = strtok(nullptr, ",");
        if (!token) continue;
        char publisher[50];
        strcpy(publisher, token);

        token = strtok(nullptr, ",");
        if (!token) continue;
        double rating = stringToDouble(token);

        token = strtok(nullptr, ",");
        if (!token) continue;
        int numDownloads = atoi(token);

        Game* game = new Game(gameID, gameName, developer, publisher, rating, numDownloads);
        gameList.addGame(game);
    }
}
int main() {
    BST bst;
    GameList gameList(100);

    // Load initial data from files
    loadPlayers(bst, "Players.txt");
    loadGames(gameList, "Games.txt");

    int choice;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Display All Games\n";
        std::cout << "2. Display All Players\n";
        std::cout << "3. Insert New Player\n";
        std::cout << "4. Insert New Game\n";
        std::cout << "5. Search Player\n";
        std::cout << "6. Search Game\n";
        std::cout << "7. Delete Player\n";
        std::cout << "8. Save Data to File\n";
        std::cout << "9. Show N Layers of Tree\n";
        std::cout << "10. Show Layer Number of Player\n";
        std::cout << "11. Show Path to Player\n";
        std::cout << "12. Edit Player\n";
        std::cout << "13. Find Top N Players\n";
        std::cout << "14. Show Player Details\n";
        std::cout << "15. Check if Player Has Played a Specific Game\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            gameList.displayAllGames();
        } 
        else if (choice == 2) {
            bst.showNLayers(10);  // Displaying up to 10 layers for demonstration
        } 
        else if (choice == 3) {
            // Insert New Player
            long long playerID;
            char playerName[50], phoneNumber[20], email[50], password[50];
            long long primaryGameID;
            double rating;
            std::cout << "Enter Player ID: "; std::cin >> playerID;
            std::cout << "Enter Player Name: "; std::cin.ignore(); std::cin.getline(playerName, 50);
            std::cout << "Enter Phone Number: "; std::cin.getline(phoneNumber, 20);
            std::cout << "Enter Email: "; std::cin.getline(email, 50);
            std::cout << "Enter Password: "; std::cin.getline(password, 50);
            std::cout << "Enter Primary Game ID: "; std::cin >> primaryGameID;
            std::cout << "Enter Rating: "; std::cin >> rating;

            Player* newPlayer = new Player(playerID, playerName, phoneNumber, email, password, primaryGameID, rating);
            bst.insert(newPlayer);
            std::cout << "Player added successfully!\n";
        } 
        else if (choice == 4) {
            // Insert New Game
            long long gameID;
            char gameName[50], developer[50], publisher[50];
            double rating;
            int numDownloads;
            std::cout << "Enter Game ID: "; std::cin >> gameID;
            std::cout << "Enter Game Name: "; std::cin.ignore(); std::cin.getline(gameName, 50);
            std::cout << "Enter Developer: "; std::cin.getline(developer, 50);
            std::cout << "Enter Publisher: "; std::cin.getline(publisher, 50);
            std::cout << "Enter Rating: "; std::cin >> rating;
            std::cout << "Enter Number of Downloads: "; std::cin >> numDownloads;

            Game* newGame = new Game(gameID, gameName, developer, publisher, rating, numDownloads);
            gameList.addGame(newGame);
            std::cout << "Game added successfully!\n";
        } 
        else if (choice == 5) {
            // Search Player
            long long playerID;
            std::cout << "Enter Player ID: ";
            std::cin >> playerID;
            Player* player = bst.search(playerID);
            if (player) {
                std::cout << "Player found: " << player->playerName << "\n";
            } else {
                std::cout << "Player not found.\n";
            }
        } 
        else if (choice == 6) {
            // Search Game
            long long gameID;
            std::cout << "Enter Game ID: ";
            std::cin >> gameID;
            Game* game = gameList.searchGame(gameID);
            if (game) {
                std::cout << "Game found: " << game->gameName << "\n";
            } else {
                std::cout << "Game not found.\n";
            }
        } 
        else if (choice == 7) {
            // Delete Player
            long long playerID;
            std::cout << "Enter Player ID to delete: ";
            std::cin >> playerID;
            bst.deletePlayer(playerID);
            std::cout << "Player deleted.\n";
        } 
        else if (choice == 8) {
            // Save Data to File
            bst.saveToFile("players_output.csv");
            std::cout << "Data saved to players_output.csv\n";
        } 
        else if (choice == 9) {
            // Show N Layers of Tree
            int layers;
            std::cout << "Enter number of layers to display: ";
            std::cin >> layers;
            bst.showNLayers(layers);
        } 
        else if (choice == 10) {
            // Show Layer Number of Player
            long long playerID;
            std::cout << "Enter Player ID: ";
            std::cin >> playerID;
            int layerNumber = bst.getLayerNumber(playerID);
            if (layerNumber != -1) {
                std::cout << "Player is at layer " << layerNumber << "\n";
            } else {
                std::cout << "Player not found.\n";
            }
        } 
        else if (choice == 11) {
            // Show Path to Player
            long long playerID;
            std::cout << "Enter Player ID: ";
            std::cin >> playerID;
            std::cout << "Path to player: ";
            bst.showPathToPlayer(playerID);
            std::cout << "\n";
        } 
        else if (choice == 12) {
            // Edit Player
            long long playerID;
            std::cout << "Enter Player ID to edit: ";
            std::cin >> playerID;
            Player* player = bst.search(playerID);
            if (player) {
                std::cout << "Editing Player: " << player->playerName << "\n";
                std::cout << "Enter new name: ";
                std::cin.ignore();
                std::cin.getline(player->playerName, 50);
                std::cout << "Player details updated.\n";
            } else {
                std::cout << "Player not found.\n";
            }
        } 
        else if (choice == 13) {
            // Find Top N Players by Number of Games
            int n;
            std::cout << "Enter N: ";
            std::cin >> n;
            bst.displayTopNPlayers(n);
        } 
        else if (choice == 14) {
            // Show Player Details
            long long playerID;
            std::cout << "Enter Player ID: ";
            std::cin >> playerID;
            Player* player = bst.search(playerID);
            if (player) {
                std::cout << "Player Details: " << player->playerName << ", Email: " << player->email << "\n";
                std::cout << "Games Played:\n";
                for (int i = 0; i < player->numGames; i++) {
                    std::cout << "  Game ID: " << player->gameIDs[i] << ", Rating: " << player->gameRatings[i] << "\n";
                }
            } else {
                std::cout << "Player not found.\n";
            }
        } 
        else if (choice == 15) {
            // Check if Player Has Played a Specific Game
            long long playerID, gameID;
            std::cout << "Enter Player ID: ";
            std::cin >> playerID;
            std::cout << "Enter Game ID: ";
            std::cin >> gameID;
            Player* player = bst.search(playerID);
            if (player) {
                bool hasPlayed = false;
                for (int i = 0; i < player->numGames; i++) {
                    if (player->gameIDs[i] == gameID) {
                        hasPlayed = true;
                        break;
                    }
                }
                if (hasPlayed) {
                    std::cout << "Player has played this game.\n";
                } else {
                    std::cout << "Player has not played this game.\n";
                }
            } else {
                std::cout << "Player not found.\n";
            }
        }

    } while (choice != 0);

    return 0;
}

