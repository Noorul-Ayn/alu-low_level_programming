#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TYPE_TEMPERATURE  0
#define TYPE_PRESSURE     1
#define TYPE_VOLTAGE      2
#define NUM_READINGS     10

struct Device {
    char name[30];
    int  type;
    union {
        float temperature;
        int   pressure;
        float voltage;
    } reading;
};

#define TEMP_MIN   15.0f
#define TEMP_MAX   85.0f
#define PRESS_MIN  80
#define PRESS_MAX  120
#define VOLT_MIN    3.0f
#define VOLT_MAX    5.5f

void temperature_monitor(struct Device *d)
{
    float t = d->reading.temperature;
    const char *status;

    if      (t < TEMP_MIN)  status = "UNDER-TEMP";
    else if (t > TEMP_MAX)  status = "OVER-TEMP";
    else                     status = "NORMAL";

    printf("[TEMP ] %-22s  %6.1f C   %s\n", d->name, t, status);
}

void pressure_monitor(struct Device *d)
{
    int p = d->reading.pressure;
    const char *status;

    if      (p < PRESS_MIN) status = "LOW PRESSURE";
    else if (p > PRESS_MAX) status = "HIGH PRESSURE";
    else                     status = "NORMAL";

    printf("[PRESS] %-22s  %6d kPa  %s\n", d->name, p, status);
}

void battery_monitor(struct Device *d)
{
    float v = d->reading.voltage;
    const char *status;

    if      (v < VOLT_MIN) status = "LOW VOLTAGE";
    else if (v > VOLT_MAX) status = "OVER VOLTAGE";
    else                    status = "NORMAL";

    printf("[VOLT ] %-22s  %6.2f V    %s\n", d->name, v, status);
}

void battery_health_monitor(struct Device *d)
{
    float v    = d->reading.voltage;
    float pct  = (v - VOLT_MIN) / (VOLT_MAX - VOLT_MIN) * 100.0f;
    if (pct < 0.0f) pct = 0.0f;
    if (pct > 100.0f) pct = 100.0f;

    const char *health;
    if      (pct >= 80) health = "Healthy";
    else if (pct >= 40) health = "Degraded";
    else                 health = "Critical";

    printf("[BATT ] %-22s  %6.2f V    Health: %.1f%% (%s)\n", d->name, v, pct, health);
}

void process_device(struct Device *d, void (*callback)(struct Device *))
{
    callback(d);
}

static float rand_float(float lo, float hi)
{
    return lo + (float)rand() / (float)RAND_MAX * (hi - lo);
}

static struct Device make_random_device(int index)
{
    struct Device d;
    int type = index % 3;
    d.type = type;

    switch (type) {
        case TYPE_TEMPERATURE:
            snprintf(d.name, sizeof(d.name), "TempSensor-%02d", index + 1);
            if (rand() % 5 == 0)
                d.reading.temperature = rand_float(85.0f, 120.0f);
            else
                d.reading.temperature = rand_float(10.0f, 85.0f);
            break;

        case TYPE_PRESSURE:
            snprintf(d.name, sizeof(d.name), "PressGauge-%02d", index + 1);
            if (rand() % 4 == 0)
                d.reading.pressure = (int)rand_float(125.0f, 200.0f);
            else
                d.reading.pressure = (int)rand_float(70.0f, 125.0f);
            break;

        case TYPE_VOLTAGE:
        default:
            snprintf(d.name, sizeof(d.name), "VoltMeter-%02d", index + 1);
            d.reading.voltage = rand_float(2.0f, 6.0f);
            break;
    }
    return d;
}

static void (*get_callback(struct Device *d))(struct Device *)
{
    switch (d->type) {
        case TYPE_TEMPERATURE: return temperature_monitor;
        case TYPE_PRESSURE:    return pressure_monitor;
        case TYPE_VOLTAGE:
        default:               return battery_monitor;
    }
}

static void print_summary(struct Device *devices, int n)
{
    int temp_alerts = 0, press_alerts = 0, volt_alerts = 0;

    /* pointer traversal */
    struct Device *ptr = devices;
    for (int i = 0; i < n; i++, ptr++) {
        switch (ptr->type) {
            case TYPE_TEMPERATURE:
                if (ptr->reading.temperature < TEMP_MIN || ptr->reading.temperature > TEMP_MAX)
                    temp_alerts++;
                break;
            case TYPE_PRESSURE:
                if (ptr->reading.pressure < PRESS_MIN || ptr->reading.pressure > PRESS_MAX)
                    press_alerts++;
                break;
            case TYPE_VOLTAGE:
                if (ptr->reading.voltage < VOLT_MIN || ptr->reading.voltage > VOLT_MAX)
                    volt_alerts++;
                break;
        }
    }

    printf("\nSimulation Summary\n");
    printf("--------------------------------------------------\n");
    printf("Total readings  : %d\n", n);
    printf("Temp alerts     : %d\n", temp_alerts);
    printf("Pressure alerts : %d\n", press_alerts);
    printf("Voltage alerts  : %d\n", volt_alerts);
    printf("Total alerts    : %d\n", temp_alerts + press_alerts + volt_alerts);
}

int main(void)
{
    srand((unsigned int)time(NULL));

    printf("\n==================================\n");
    printf("  DEVICE MONITORING SIMULATOR\n");
    printf("  Student ID : 54321\n");
    printf("  Custom CB  : Battery Health Monitor\n");
    printf("==================================\n");

    struct Device *devices = (struct Device *)malloc(NUM_READINGS * sizeof(struct Device));
    if (!devices) { perror("malloc"); return EXIT_FAILURE; }

    printf("\ndevices array at memory address: %p\n", (void *)devices);

    /* pointer traversal to fill devices */
    struct Device *ptr = devices;
    for (int i = 0; i < NUM_READINGS; i++, ptr++)
        *ptr = make_random_device(i);

    printf("\nStandard Monitoring (readings 1-%d)\n", NUM_READINGS);
    printf("------------------------------------------------------\n");
    printf("%-6s  %-22s  %-12s  %s\n", "Type", "Device", "Value", "Status");
    printf("------------------------------------------------------\n");

    /* pointer traversal for monitoring */
    ptr = devices;
    for (int i = 0; i < NUM_READINGS; i++, ptr++) {
        process_device(ptr, get_callback(ptr));
    }

    printf("\nBattery Health Report (Voltage Devices Only)\n");
    printf("------------------------------------------------------\n");
    int found = 0;
    ptr = devices;
    for (int i = 0; i < NUM_READINGS; i++, ptr++) {
        if (ptr->type == TYPE_VOLTAGE) {
            process_device(ptr, battery_health_monitor);
            found++;
        }
    }
    if (!found) printf("No voltage devices found.\n");

    print_summary(devices, NUM_READINGS);

    free(devices);
    printf("\nMemory freed. Simulation complete.\n");
    return 0;
}
