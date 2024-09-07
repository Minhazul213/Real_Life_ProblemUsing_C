#include <stdio.h>
#include <stdlib.h>

void sortDescending(int people[], int camps) {
    for (int i = 0; i < camps - 1; i++) {
        for (int j = i + 1; j < camps; j++) {
            if (people[i] < people[j]) {
                int temp = people[i];
                people[i] = people[j];
                people[j] = temp;
            }
        }
    }
}

void calculateAndDisplay(int totalPeople, int foodPackets) {
    if (totalPeople > foodPackets) {
        int shortage = totalPeople - foodPackets;
        printf("Total %d people are present, which requires %d more packets than the %d available packets.\n", totalPeople, shortage, foodPackets);
    } else if (totalPeople < foodPackets) {
        int extraPackets = foodPackets - totalPeople;
        printf("Total %d people are present, and there will be %d extra packets.\n", totalPeople, extraPackets);
    } else {
        printf("Total %d people are present and all packets are sufficient.\n", totalPeople);
    }
}

void checkUrgency(int campNumber, int people[], int* camps, int* foodPackets) {
    if (campNumber > 0 && campNumber <= *camps) {
        printf("Camp %d has %d people.\n", campNumber, people[campNumber - 1]);

        int requiredPackets = people[campNumber - 1];
        if (*foodPackets >= requiredPackets) {
            *foodPackets -= requiredPackets;
            printf("Distribute %d packets to Camp %d.\n", requiredPackets, campNumber);
            printf("Remaining packets: %d\n", *foodPackets);

            for (int i = campNumber - 1; i < *camps - 1; i++) {
                people[i] = people[i + 1];
            }
            (*camps)--;

            int totalPeople = 0;
            for (int i = 0; i < *camps; i++) {
                totalPeople += people[i];
            }

            calculateAndDisplay(totalPeople, *foodPackets);
        } else {
            printf("Not enough packets. Packets required: %d\n", requiredPackets);
        }
    } else {
        printf("Invalid camp number.\n");
    }
}

int main() {
    int camps;
    int foodPackets;

    printf("Enter the number of camps: ");
    scanf("%d", &camps);

    printf("Enter the number of food packets: ");
    scanf("%d", &foodPackets);

    int* people = (int*)malloc(camps * sizeof(int));
    int totalPeople = 0;

    for (int i = 0; i < camps; i++) {
        printf("Enter the number of people in Camp %d: ", i + 1);
        scanf("%d", &people[i]);
        totalPeople += people[i];
    }

    calculateAndDisplay(totalPeople, foodPackets);
    sortDescending(people, camps);

    printf("Camps sorted by number of people (descending):\n");
    for (int i = 0; i < camps; i++) {
        printf("Camp %d has %d people.\n", i + 1, people[i]);
    }

    int urgentCamp;
    while (camps > 0) {
        printf("Enter the camp number for urgent relief distribution (1-%d): ", camps);
        scanf("%d", &urgentCamp);
        checkUrgency(urgentCamp, people, &camps, &foodPackets);

        sortDescending(people, camps);

        printf("Camps sorted by number of people (descending):\n");
        for (int i = 0; i < camps; i++) {
            printf("Camp %d has %d people.\n", i + 1, people[i]);
        }

        if (camps == 0) {
            printf("Relief distribution completed in all camps.\n");
            break;
        }
    }

    free(people);
    return 0;
}
