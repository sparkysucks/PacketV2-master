#include "Killsults.h"

using namespace std;
Killsults::Killsults() : IModule(0, Category::OTHER, "Insults people you kill lol") {
    registerEnumSetting("Mode", &mode, 0);
    mode.addEntry("Normal", 0);
    mode.addEntry("Sigma", 1);
    //mode.addEntry("Custom", 2);
}

const char* Killsults::getRawModuleName() {
    return "Killsults";
}

const char* Killsults::getModuleName() {
    if (mode.getSelectedValue() == 0) name = string("Killsults ") + string(GRAY) + string("Normal");
    if (mode.getSelectedValue() == 1) name = string("Killsults ") + string(GRAY) + string("Custom");
    return name.c_str();
}

string normalMessages[36] = {
    "Download balls today to kick azs while aiding to some bo burnham!",
    "Say goodbye to your kneecaps, Chucklehead!",
    "What's yellow and can't swim? A bus full of children",
    "You are more disappointing than an unsalted pretzel",
    "want a break from the aids? download balls!",
    "You are not balls approved",
    "I'm not flying.",
    "killed",
    "Knock knock. The swat team is here.",
    "you use discord light mode",
    "How do Jews go to heaven? Well done.",
    "im not cheating im just a leaderboard player",
    "certified monkey",
    "you got aided by balls client",
    "Whats better that winning gold at the paralympics? Walking.",
    "best legit ww",
    "JACKALOPE TURD BOX",
    "you probably put pineapple on pizza",
    "Get 360 No-Scoped",
    "srxfiq is cool",
    "Go do the dishes",
    "Job Immediately",
    "Delete System32",
    "zephyr stinky",
    "Touch grass",
    "jajajaja",
    "Minority",
    "kkkkkk",
    "clean",
    "idot",
    "balls 1",
};

string cheaterMessages[9] = {
    "How does this bypass ?!?!?",
    "Switch to ballsv69 today!",
    "Violently bhopping I see!",
    "Why Zephyr when Packet?",
    "You probably use Zephyr",
    "Must be using Kek.Club+",
    "SelfH4rm Immediately.",
    "Man you're violent",
    "Horion moment"
};

string sigmaMessages[2] = {
    "Eat My",
    "Funny Funny Abstractional"
};

void Killsults::onEnable() {
    killed = false;
}

void Killsults::onPlayerTick(C_Player* plr) {
    auto player = g_Data.getLocalPlayer();
    if (player == nullptr) return;

    int random = 0;
    srand(time(NULL));
    if (killed) {
        C_TextPacket textPacket;
        switch (mode.getSelectedValue()) {
        case 0: // Normal
            random = rand() % 36;
            textPacket.message.setText(normalMessages[random]);
            break;
        case 1: // Sigma
            random = rand() % 2;
            textPacket.message.setText(sigmaMessages[random]);
            break;
        case 2: //cheater
            random = rand() % 28;
            textPacket.message.setText(cheaterMessages[random]);
        }
        textPacket.sourceName.setText(player->getNameTag()->getText());
        textPacket.xboxUserId = to_string(player->getUserId());
        g_Data.getClientInstance()->loopbackPacketSender->sendToServer(&textPacket);
        killed = false;
    }
}