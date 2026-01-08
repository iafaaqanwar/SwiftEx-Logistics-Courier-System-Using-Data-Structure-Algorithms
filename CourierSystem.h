/**
 * CourierSystem.h
 * 
 * Header file for the Intelligent Courier Logistics Engine
 * 
 * This class implements a comprehensive courier management system with:
 * 1. Intelligent Parcel Sorting Module
 *    - Multi-criteria sorting (priority, weight, destination)
 *    - Real-time insertion and withdrawal
 * 
 * 2. Parcel Routing Module
 *    - Shortest path calculation (Dijkstra's)
 *    - Multiple alternative routes (K-shortest paths)
 *    - Blocked/overloaded path handling
 *    - Dynamic route recalculation
 * 
 * 3. Parcel Tracking System
 *    - Complete lifecycle tracking
 *    - Timestamped history
 *    - Delivery attempt tracking
 *    - Return to sender functionality
 * 
 * 4. Courier Operations Engine
 *    - Separate queues (pickup, warehouse, transit)
 *    - Rider management with capacity tracking
 *    - Missing parcel detection
 *    - Operation logging and undo/replay
 * 
 * Data Structure Justification:
 * - HashTable: O(1) average-case parcel lookup (vs O(n) with Vector)
 * - MinHeap: O(log n) priority queue for warehouse sorting
 * - Queue: FIFO ordering for pickup and transit stages
 * - Graph: Efficient route representation and pathfinding
 * - Stack: LIFO for undo operations
 */

#ifndef COURIER_SYSTEM_H
#define COURIER_SYSTEM_H

#include "DataStructures.h"
#include "Models.h"
#include "Utils.h"
#include <limits>
#include <algorithm>
#include <ctime>
#include <sstream>

using namespace std;

class CourierSystem {
private:
    Graph<City> cityMap;
    
    // Separate queues for different stages
    Queue<Parcel> pickupQueue;           // Parcels waiting for pickup
    MinHeap<Parcel> warehouseQueue;      // Parcels in warehouse (priority-sorted)
    Queue<Parcel> transitQueue;          // Parcels in transit
    
    // Hash table for O(1) parcel lookup
    HashTable<int, Parcel*> parcelMap;
    
    // Vector for iteration (maintains all parcels)
    Vector<Parcel> allParcels;
    
    // Rider management
    Vector<Rider> riders;
    int nextRiderID;
    
    // Admin management
    Vector<Admin> admins;
    
    // Blocked routes
    Vector<BlockedEdge> blockedEdges;
    
    // Overloaded paths (with load/capacity tracking)
    struct OverloadedEdge {
        int srcID;
        int destID;
        int currentLoad;
        int maxCapacity;
        OverloadedEdge() : srcID(-1), destID(-1), currentLoad(0), maxCapacity(100) {}
        OverloadedEdge(int s, int d, int load, int cap) : srcID(s), destID(d), currentLoad(load), maxCapacity(cap) {}
    };
    Vector<OverloadedEdge> overloadedEdges;
    
    // Operation logging for undo/replay
    Stack<OperationLog> operationHistory;
    
    int nextTrackingID;
    
    // Helper: Get current timestamp as string
string getCurrentTimestamp() const;
    
    // Helper: Log an operation
    void logOperation(OperationType type, int parcelID, const string& prevState, 
                     const string& newState, int riderID = -1, int srcID = -1, int destID = -1);
    
    // Helper: Check if edge is blocked
    bool isEdgeBlocked(int srcID, int destID) const;
    
    // Helper: Find parcel by ID using hash table
    Parcel* findParcel(int trackingID);
    
    // Validation helpersl
    bool validateCityID(int cityID) const;
    bool validateRoute(int srcID, int destID) const;
    bool validateParcelData(int weight, int srcID, int destID) const;
    
    // Queue helper functions for undo operations
    bool isParcelInQueue(const Queue<Parcel>& queue, int parcelID) const;
    bool isParcelInHeap(const MinHeap<Parcel>& heap, int parcelID) const;
    void removeParcelFromQueue(Queue<Parcel>& queue, int parcelID);
    void removeParcelFromHeap(MinHeap<Parcel>& heap, int parcelID);

public:
    CourierSystem();
    
    void loadData();
    void saveData(); // Save all data to files
    
    // Core Features
    void addParcel(string sender, string receiver, Priority priority, int weight, int srcID, int destID);
    bool removeParcel(int trackingID); // Real-time withdrawal
    void addCity(string name);
    void addRoute(int srcID, int destID, int distance);
    
    // Intelligent Parcel Sorting
    Vector<Parcel> getParcelsByWeightCategory(WeightCategory category);
    Vector<Parcel> getParcelsByDestination(int destCityID);
    Vector<Parcel> getFragileParcels();
    void sortParcelsByWeight(Vector<Parcel>& parcels);
    void sortParcelsByDestination(Vector<Parcel>& parcels);
    void sortParcelsByPriority(Vector<Parcel>& parcels);
    void displayParcelsByWeight();
    void displayParcelsByDestination();
    void displayParcelsByPriority();
    void markParcelAsFragile(int trackingID);
    
    // Routing - Enhanced
    void displayRoute(int srcID, int destID);
    void viewAllRoutes(int srcID, int destID); // View all possible routes
    int calculateShortestPath(int srcID, int destID, Vector<int>& path, bool avoidBlocked = true);
    void calculateAlternativeRoutes(int srcID, int destID, int k, Vector<Vector<int>>& routes, Vector<int>& distances);
    void displayAlternativeRoutes(int srcID, int destID, int count);
    
    // Blocked Path Handling
    void blockRoute(int srcID, int destID);
    void unblockRoute(int srcID, int destID);
    void displayBlockedRoutes();
    void recalculateActiveRoutes(); // Recalculate routes for in-transit parcels
    
    // Operations - Enhanced
    void processNextParcel(); // Pickup -> Warehouse
    void processParcelByID(int parcelID); // Process specific parcel by ID
    void assignRider();       // Warehouse -> Transit (basic)
    void assignRiderToParcel(int parcelID, int riderID); // Enhanced assignment
    int findAvailableRider(int requiredCapacity, int cityID);
    void completeDelivery();  // Transit -> Delivered
    void completeDeliveryByID(int parcelID); // Complete delivery for specific parcel by ID
    void recordDispatch(int trackingID);
    void recordLoading(int trackingID, int cityID);
    void recordUnloading(int trackingID, int cityID);
    void recordDeliveryAttempt(int trackingID, bool success);
    void returnToSender(int trackingID);
    
    // Rider Management
    void addRider(string name, int capacity, int cityID);
    void displayRiders();
    void displayRiderLoad(int riderID);
    void displayAllRiderLoads();
    
    // Queue Management
    void displayQueueStatus();
    
    // Missing Parcel Detection
    void detectMissingParcels();
    
    // Operation Logging and Undo
    void undoLastOperation();
    void displayOperationLog();
    void saveOperationLog(const string& filename);
    void loadOperationLog(const string& filename);
    
    // Reporting - Enhanced
    void trackParcel(int trackingID);
    void displayAllParcels();
    void displayCities();
    
    // Statistics and Reporting
    void displayDeliveryStatistics();
    void displayRiderStatistics(int riderID);
    double getAverageDeliveryTime(Priority priority);
    int getDeliverySuccessRate();
    
    // Admin Management
    void initializeAdmins(); // Initialize with super admin
    bool authenticateAdmin(const string& username, const string& password);
    void addAdmin(string username, string password);
    bool removeAdmin(string username);
    void displayAdmins();
    void loadAdmins();
    void saveAdmins();
    
    // Overloaded Path Handling
    void markPathAsOverloaded(int srcID, int destID, int load);
    void unmarkPathAsOverloaded(int srcID, int destID);
    bool isPathOverloaded(int srcID, int destID) const;
    void displayOverloadedRoutes();
    
private:
    // Dijkstra's Algorithm Helper
    struct DijkstraNode {
        int id;
        int dist;
        bool operator<(const DijkstraNode& other) const {
            return dist > other.dist; // MinHeap needs smallest dist at top
        }
        bool operator>(const DijkstraNode& other) const {
            return dist < other.dist;
        }
    };
    
    // K-shortest paths helper (simplified Yen's algorithm)
    void findKShortestPaths(int srcID, int destID, int k, Vector<Vector<int>>& paths, Vector<int>& distances);
};

#endif
