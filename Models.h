#ifndef MODELS_H
#define MODELS_H

#include <string>
#include "DataStructures.h"

using namespace std;

enum class Priority {
    Overnight = 1,
    TwoDay = 2,
    Normal = 3
};

enum class Status {
    Pending,
    PickedUp,
    InWarehouse,
    InTransit,
    Delivered,
    Returned,
    Missing
};

enum class WeightCategory {
    Light = 1,    // 0-5 kg
    Medium = 2,   // 5-20 kg
    Heavy = 3     // 20+ kg
};

struct City {
    int id;
string name;
    
    City() : id(-1), name("") {}
    City(int i, string n) : id(i), name(n) {}
};

struct Parcel {
    int trackingID;
string senderName;
string receiverName;
    Priority priority;
    int weight; // in kg
    Status status;
    int sourceCityID;
    int destCityID;
    int currentCityID; // Current location during transit
    Vector<int> currentRoute; // Assigned route path
    LinkedList<string> history;
    int deliveryAttempts; // Track number of delivery attempts
    bool isFragile; // Fragile parcel flag

    Parcel() : trackingID(-1), weight(0), status(Status::Pending), sourceCityID(-1), destCityID(-1),
               currentCityID(-1), deliveryAttempts(0), isFragile(false) {}
    
    Parcel(int id, string s, string r, Priority p, int w, int src, int dest)
        : trackingID(id), senderName(s), receiverName(r), priority(p), weight(w), 
          status(Status::Pending), sourceCityID(src), destCityID(dest), currentCityID(src),
          deliveryAttempts(0), isFragile(false) {
        history.push_back("Parcel Created");
    }
    
    // Equality operator for Queue and MinHeap remove operations
    bool operator==(const Parcel& other) const {
        return trackingID == other.trackingID;
    }

    // Get weight category based on weight
    // Time Complexity: O(1)
    WeightCategory getWeightCategory() const {
        if (weight < 5) return WeightCategory::Light;
        if (weight < 20) return WeightCategory::Medium;
        return WeightCategory::Heavy;
    }
    
string getWeightCategoryStr() const {
        switch(getWeightCategory()) {
            case WeightCategory::Light: return "Light (0-5kg)";
            case WeightCategory::Medium: return "Medium (5-20kg)";
            case WeightCategory::Heavy: return "Heavy (20+kg)";
            default: return "Unknown";
        }
    }

    // Operator for Priority Queue (MinHeap) - Enhanced with weight and destination
    // Primary: Priority, Secondary: Fragile (fragile parcels prioritized), Tertiary: Weight, Quaternary: Destination, Quinary: Tracking ID
    // Time Complexity: O(1)
    bool operator<(const Parcel& other) const {
        // Primary: Priority (lower enum = higher priority)
        if (priority != other.priority) {
            return priority < other.priority;
        }
        // Secondary: Fragile parcels get higher priority (need special handling)
        // Non-fragile < Fragile (so fragile comes first in min-heap)
        if (isFragile != other.isFragile) {
            return !isFragile; // If this is not fragile and other is fragile, this < other (fragile prioritized)
        }
        // Tertiary: Weight category (lighter parcels first for efficiency)
        WeightCategory thisCat = getWeightCategory();
        WeightCategory otherCat = other.getWeightCategory();
        if (thisCat != otherCat) {
            return thisCat < otherCat; // Light < Medium < Heavy
        }
        // Quaternary: Destination (group by destination for route optimization)
        if (destCityID != other.destCityID) {
            return destCityID < other.destCityID;
        }
        // Quinary: Tracking ID (FIFO for same priority/fragile/weight/destination)
        return trackingID < other.trackingID;
    }
    
    bool operator>(const Parcel& other) const {
        return other < *this;
    }
    
string getPriorityStr() const {
        switch(priority) {
            case Priority::Overnight: return "Overnight";
            case Priority::TwoDay: return "Two-Day";
            case Priority::Normal: return "Normal";
            default: return "Unknown";
        }
    }
    
string getStatusStr() const {
        switch(status) {
            case Status::Pending: return "Pending";
            case Status::PickedUp: return "Picked Up";
            case Status::InWarehouse: return "In Warehouse";
            case Status::InTransit: return "In Transit";
            case Status::Delivered: return "Delivered";
            case Status::Returned: return "Returned";
            case Status::Missing: return "Missing";
            default: return "Unknown";
        }
    }
};

struct Rider {
    int riderID;
string name;
    int capacity; // Maximum weight capacity in kg
    int currentLoad; // Current weight of assigned parcels
    int currentCityID;
    Vector<int> assignedParcels; // List of tracking IDs assigned to this rider
    
    Rider() : riderID(-1), capacity(0), currentLoad(0), currentCityID(-1) {}
    Rider(int id, string n, int cap, int city) 
        : riderID(id), name(n), capacity(cap), currentLoad(0), currentCityID(city) {}
    
    // Check if rider can carry additional weight
    bool canCarry(int weight) const {
        return (currentLoad + weight) <= capacity;
    }
    
    // Get available capacity
    int getAvailableCapacity() const {
        return capacity - currentLoad;
    }
};

// Operation Log structure for undo/replay functionality
enum class OperationType {
    AddParcel,
    RemoveParcel,
    ProcessParcel,
    AssignRider,
    CompleteDelivery,
    BlockRoute,
    UnblockRoute,
    ReturnToSender
};

struct OperationLog {
    OperationType type;
string timestamp;
    int parcelID;
string previousState;
string newState;
    int riderID; // For rider-related operations
    int srcID, destID; // For route operations
    
    OperationLog() : type(OperationType::AddParcel), parcelID(-1), riderID(-1), srcID(-1), destID(-1) {}
};

// Blocked Edge structure for route management
struct BlockedEdge {
    int srcID;
    int destID;
    bool isBlocked;
    
    BlockedEdge() : srcID(-1), destID(-1), isBlocked(false) {}
    BlockedEdge(int s, int d, bool blocked) : srcID(s), destID(d), isBlocked(blocked) {}
    
    bool operator==(const BlockedEdge& other) const {
        return (srcID == other.srcID && destID == other.destID) ||
               (srcID == other.destID && destID == other.srcID); // Undirected
    }
};

// Admin structure for system access control
struct Admin {
    string username;
    string password;
    bool isSuperAdmin;
    
    Admin() : username(""), password(""), isSuperAdmin(false) {}
    Admin(string user, string pass, bool superAdmin = false) 
        : username(user), password(pass), isSuperAdmin(superAdmin) {}
    
    bool operator==(const Admin& other) const {
        return username == other.username;
    }
};

#endif
