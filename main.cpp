#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <optional>

class InMemoryDB {
private:
    std::unordered_map<std::string, int> mainState;
    std::unordered_map<std::string, int> transactionState;
    bool inTransaction = false;

public:
    std::optional<int> get(const std::string& key) {
        if (isKeyInTransactionState(key)) {
            return transactionState[key];
        } else if (mainState.find(key) != mainState.end()) {
            return mainState[key];
        } else {
            return {}; // Equivalent to std::nullopt
        }
    }

    void put(const std::string& key, int val) {
        checkTransactionInProgress();
        transactionState[key] = val;
    }

    void begin_transaction() {
        if (inTransaction) {
            throw std::runtime_error("Transaction already in progress");
        }
        inTransaction = true;
    }

    void commit() {
        checkTransactionInProgress();
        applyTransactionStateToMain();
        clearTransactionState();
    }

    void rollback() {
        checkTransactionInProgress();
        clearTransactionState();
    }

private:
    void clearTransactionState() {
        transactionState.clear();
        inTransaction = false;
    }

    void applyTransactionStateToMain() {
        for (const auto& entry : transactionState) {
            mainState[entry.first] = entry.second;
        }
    }

    void checkTransactionInProgress() {
        if (!inTransaction) {
            throw std::runtime_error("No transaction in progress");
        }
    }

    bool isKeyInTransactionState(const std::string& key) {
        return inTransaction && transactionState.count(key) > 0;
    }
};

void printValue(const std::optional<int>& value) {
    if (value) {
        std::cout << value.value() << std::endl;
    } else {
        std::cout << "null" << std::endl;
    }
}

int main() {
    InMemoryDB inmemoryDB;

    printValue(inmemoryDB.get("A"));

    try {
        inmemoryDB.put("A", 5);
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    inmemoryDB.begin_transaction();
    inmemoryDB.put("A", 5);
    printValue(inmemoryDB.get("A"));
    inmemoryDB.put("A", 6);
    inmemoryDB.commit();
    printValue(inmemoryDB.get("A"));

    try {
        inmemoryDB.commit();
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        inmemoryDB.rollback();
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    printValue(inmemoryDB.get("B"));

    inmemoryDB.begin_transaction();
    inmemoryDB.put("B", 10);
    inmemoryDB.rollback();
    printValue(inmemoryDB.get("B"));

    return 0;
}
