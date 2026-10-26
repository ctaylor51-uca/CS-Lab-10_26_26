#include <iostream>
#include <string>

// ==========================================
// PART ONE: DEFAULT ARGUMENTS
// ==========================================

// 1. Displays a spell casting banner with default arguments
void displaySpellBanner(std::string spellName, std::string tier = "Novice", int chargeLevel = 1) {
    std::cout << "\n========================================\n";
    std::cout << "  CASTING: " << spellName << " (" << tier << " Tier)\n";
    std::cout << "  Charge Level: [" << chargeLevel << "]\n";
    std::cout << "========================================\n";
}

// 2. Prints attack summary and calculates damage with default arguments
double castSpell(std::string spellName = "Magic Missile", int basePower = 10, double multiplier = 1.0) {
    double totalDamage = basePower * multiplier;
    std::cout << "  >> " << spellName << " deals " << totalDamage << " base damage!\n";
    return totalDamage;
}

// 3. Calculates total absorbed damage with default arguments
double calculateShield(double baseShield = 15.0, double absorptionRate = 0.2) {
    return baseShield * (1.0 + absorptionRate);
}

// ==========================================
// PART TWO: STATIC LOCAL VARIABLES
// ==========================================

// 1. Tracks and returns consecutive hitting streaks
int registerCombo(bool hitSuccessful) {
    static int comboCount = 0;

    if (hitSuccessful) {
        comboCount++;
    }
    else {
        comboCount = 0;
        std::cout << "  [!] Combo broken! Your streak dropped to 0.\n";
    }
    return comboCount;
}

// 2. Accumulates and tracks overall mana expenditure
void consumeMana(int cost = 5) {
    static int totalManaUsed = 0;
    totalManaUsed += cost;
    std::cout << "  [Mana Spent: " << cost << " | Total Duel Mana Expended: " << totalManaUsed << "]\n";
}

// 3. Accumulates total damage to trigger Boss Enrage Mode
bool processBossRage(double damageDealt) {
    static double totalDamageDealt = 0.0;
    totalDamageDealt += damageDealt;

    if (totalDamageDealt >= 100.0) {
        return true;
    }
    return false;
}

// 4. Handles persistent XP gains and levels up the user
int gainWizardXP(int expGained = 25) {
    static int totalXP = 0;
    static int wizardLevel = 1;

    totalXP += expGained;
    std::cout << "  [XP Gained: +" << expGained << " | Total XP: " << totalXP << "]\n";

    if (totalXP >= (wizardLevel * 100)) {
        wizardLevel++;
        std::cout << "\n✨✨ LEVEL UP! You are now a Level " << wizardLevel << " Wizard! ✨✨\n";
    }
    return wizardLevel;
}

// ==========================================
// MAIN BATTLE SIMULATOR LOOP
// ==========================================
int main() {
    std::cout << "=== WIZARD ACADEMY BATTLE SIMULATOR ===\n\n";

    char continueBattle = 'y';
    int turn = 1;

    while (continueBattle == 'y' || continueBattle == 'Y') {
        std::cout << "\n----------------------------------------\n";
        std::cout << " TURN " << turn << "\n";
        std::cout << "----------------------------------------\n";

        int choice = 0;
        std::cout << "Select Action:\n";
        std::cout << "1) Quick Magic Missile (Default attack)\n";
        std::cout << "2) Heavy Lightning Storm (Custom attack)\n";
        std::cout << "3) Cast Defensive Barrier\n";
        std::cout << "4) Miss Attack Intentionally\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        double damageDealt = 0.0;
        bool successfulHit = false;

        if (choice == 1) {
            displaySpellBanner("Magic Missile");
            damageDealt = castSpell(); // Uses default arguments
            consumeMana();             // Uses default mana cost (5)
            successfulHit = true;
        }
        else if (choice == 2) {
            displaySpellBanner("Lightning Storm", "Adept", 2);
            damageDealt = castSpell("Lightning Storm", 30, 1.4);
            consumeMana(15);           // Custom mana cost
            successfulHit = true;
        }
        else if (choice == 3) {
            displaySpellBanner("Arcane Shield", "Novice", 1);
            double shieldVal = calculateShield(20.0, 0.25);
            std::cout << "Shield generated! Absorbs " << shieldVal << " incoming damage.\n";
            consumeMana(8);
            successfulHit = true;
        }
        else {
            std::cout << "Your attack missed completely!\n";
            successfulHit = false;
        }

        // --- UPDATE PERSISTENT GAME STATE VIA STATIC FUNCTIONS ---
        int currentCombo = registerCombo(successfulHit);
        if (successfulHit) {
            std::cout << "Current Combo Streak: " << currentCombo << "x\n";
            gainWizardXP(30); // Award XP for hitting
        }

        // Check if boss enters enrage mode
        bool isBossEnraged = processBossRage(damageDealt);
        if (isBossEnraged) {
            std::cout << "!!! WARNING: BOSS HAS ENTERED ENRAGE MODE !!!\n";
        }

        turn++;
        std::cout << "\nEnd turn? Continue fighting? (y/n): ";
        std::cin >> continueBattle;
    }

    std::cout << "\n=== BATTLE SIMULATION ENDED ===\n";
    return 0;
}