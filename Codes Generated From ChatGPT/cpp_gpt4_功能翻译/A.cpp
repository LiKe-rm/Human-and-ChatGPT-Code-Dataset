#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <vector>
#include <stdexcept>

class AccessibilityAction {
public:
    int id;
    std::string label;

    AccessibilityAction(int id, const std::string& label) : id(id), label(label) {}
};

class Action {
public:
    static const Action ACTION_1;
    static const Action ACTION_2;
    static const Action ACTION_4;
    // ...

    int id() const {
        return action->id;
    }

    std::string label() const {
        return action->label;
    }

    bool operator==(const Action& other) const {
        return action->id == other.action->id && action->label == other.action->label;
    }

    bool operator!=(const Action& other) const {
        return !(*this == other);
    }

protected:
    std::shared_ptr<AccessibilityAction> action;

    Action(int id, const std::string& label) : action(std::make_shared<AccessibilityAction>(id, label)) {}
};

const Action Action::ACTION_1 = Action(1, "Action 1");
const Action Action::ACTION_2 = Action(2, "Action 2");
const Action Action::ACTION_4 = Action(4, "Action 4");
// ...

class ActionSubClass : public Action {
public:
    ActionSubClass(int id, const std::string& label) : Action(id, label) {}
};

// ...

int main() {
    std::vector<Action> actions = {Action::ACTION_1, Action::ACTION_2, Action::ACTION_4};
    Action action1 = actions[0];
    Action action2 = actions[1];

    std::cout << "Action 1 ID: " << action1.id() << std::endl;
    std::cout << "Action 1 Label: " << action1.label() << std::endl;

    if (action1 == action2) {
        std::cout << "Actions are equal." << std::endl;
    } else {
        std::cout << "Actions are not equal." << std::endl;
    }

    return 0;
}
