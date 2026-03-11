#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct WordStat {
    char name[40];
    int  count;
};

static char          *text_buffer  = NULL;
static char         **word_array   = NULL;
static struct WordStat *stats      = NULL;
static int            word_count   = 0;
static int            unique_count = 0;

static const char *sample_text =
    "We find ourselves in a bewildering world. We want to make sense of "
    "what we see around us and to ask what is the nature of the universe. "
    "Is it infinite or does it have boundaries? Did time have a beginning "
    "and will it have an end? Are we really free to make our own choices "
    "or is everything determined and we just think it is free?";

static int is_vowel(char c)
{
    c = (char)tolower((unsigned char)c);
    return (c=='a'||c=='e'||c=='i'||c=='o'||c=='u');
}

static char *clean_word(const char *w)
{
    static char buf[80];
    int j = 0;
    for (int i = 0; w[i] && j < 79; i++)
        if (isalpha((unsigned char)w[i]))
            buf[j++] = (char)tolower((unsigned char)w[i]);
    buf[j] = '\0';
    return buf;
}

static void load_text(void)
{
    free(text_buffer);
    size_t len = strlen(sample_text) + 1;
    text_buffer = (char *)malloc(len);
    if (!text_buffer) { perror("malloc"); exit(EXIT_FAILURE); }
    strcpy(text_buffer, sample_text);
    printf("\nText loaded (%zu bytes).\n", len - 1);
    printf("text_buffer stored at memory address : %p\n", (void *)text_buffer);
}

static void split_words(void)
{
    char *copy = strdup(text_buffer);
    if (!copy) { perror("strdup"); return; }

    word_count = 0;
    char *tok = strtok(copy, " \t\n\r.,!?;:\"'()-");
    while (tok) { word_count++; tok = strtok(NULL, " \t\n\r.,!?;:\"'()-"); }
    free(copy);

    free(word_array);
    word_array = (char **)malloc((size_t)word_count * sizeof(char *));
    if (!word_array) { perror("malloc"); return; }

    copy = strdup(text_buffer);
    int idx = 0;
    tok = strtok(copy, " \t\n\r.,!?;:\"'()-");
    while (tok && idx < word_count) {
        word_array[idx] = strdup(tok);
        idx++;
        tok = strtok(NULL, " \t\n\r.,!?;:\"'()-");
    }
    free(copy);
    printf("word_array stored at memory address  : %p\n", (void *)word_array);
    printf("Total words: %d\n", word_count);
}

static void build_stats(void)
{
    free(stats);
    stats = (struct WordStat *)malloc((size_t)word_count * sizeof(struct WordStat));
    if (!stats) { perror("malloc"); return; }
    unique_count = 0;

    for (int i = 0; i < word_count; i++) {
        char *cw = clean_word(word_array[i]);
        if (cw[0] == '\0') continue;

        int found = 0;
        for (int j = 0; j < unique_count; j++) {
            if (strcmp(stats[j].name, cw) == 0) {
                stats[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strncpy(stats[unique_count].name, cw, sizeof(stats[unique_count].name) - 1);
            stats[unique_count].name[sizeof(stats[unique_count].name)-1] = '\0';
            stats[unique_count].count = 1;
            unique_count++;
        }
    }
    printf("stats array stored at memory address : %p\n", (void *)stats);
    printf("Unique words: %d\n", unique_count);
}

static void count_words(void)
{
    if (!word_array) { printf("\nLoad text first.\n"); return; }
    printf("\nWord Count: %d\n", word_count);
    printf("Unique Words: %d\n", unique_count);
}

static void longest_word(void)
{
    if (!word_array) { printf("\nLoad text first.\n"); return; }

    char *longest = word_array[0];
    char **ptr = word_array + 1;
    for (int i = 1; i < word_count; i++, ptr++)
        if (strlen(*ptr) > strlen(longest)) longest = *ptr;

    printf("\nLongest Word: \"%s\" (%zu letters)\n", longest, strlen(longest));
}

static void most_frequent(void)
{
    if (!stats) { printf("\nLoad text first.\n"); return; }

    struct WordStat *top = &stats[0];
    for (int i = 1; i < unique_count; i++)
        if (stats[i].count > top->count) top = &stats[i];

    printf("\nMost Frequent: \"%s\" (%d times)\n", top->name, top->count);
}

static void vowel_density(void)
{
    if (!text_buffer) { printf("\nLoad text first.\n"); return; }

    int total_letters = 0, total_vowels = 0;
    char *ptr = text_buffer;
    while (*ptr) {
        if (isalpha((unsigned char)*ptr)) {
            total_letters++;
            if (is_vowel(*ptr)) total_vowels++;
        }
        ptr++;
    }

    float density = (total_letters > 0) ? (float)total_vowels / (float)total_letters * 100.0f : 0.0f;

    printf("\nVowel Density\n");
    printf("Letters: %d\n", total_letters);
    printf("Vowels: %d\n", total_vowels);
    printf("Density: %.2f%%\n", density);

    if      (density > 45) printf("Verdict: Vowel-rich\n");
    else if (density > 35) printf("Verdict: Average\n");
    else                    printf("Verdict: Consonant-heavy\n");
}

static void free_all(void)
{
    free(text_buffer); text_buffer = NULL;
    if (word_array) {
        for (int i = 0; i < word_count; i++) free(word_array[i]);
        free(word_array); word_array = NULL;
    }
    free(stats); stats = NULL;
    word_count = unique_count = 0;
}

typedef void (*AnalysisFn)(void);
AnalysisFn analysis_fns[] = { count_words, longest_word, most_frequent, vowel_density };

int main(void)
{
    printf("\n==================================\n");
    printf("  ADAPTIVE TEXT INTELLIGENCE TOOL\n");
    printf("  Student ID : 54321\n");
    printf("  Analysis   : Vowel Density\n");
    printf("==================================\n");

    load_text();
    split_words();
    build_stats();

    int choice;
    do {
        printf("\nMENU\n");
        printf("1. Count Words\n");
        printf("2. Longest Word\n");
        printf("3. Most Frequent\n");
        printf("4. Vowel Density\n");
        printf("5. Show Text\n");
        printf("6. Custom Text\n");
        printf("7. Exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) choice = 7;

        if (choice >= 1 && choice <= 4) {
            analysis_fns[choice - 1]();
        } else if (choice == 5) {
            printf("\nText:\n\"%s\"\n", text_buffer);
        } else if (choice == 6) {
            printf("\nEnter text:\n> ");
            char buf[1024];
            scanf(" %1023[^\n]", buf);
            free_all();
            text_buffer = strdup(buf);
            printf("text_buffer now at memory address : %p\n", (void *)text_buffer);
            split_words();
            build_stats();
        } else if (choice != 7) {
            printf("\nInvalid choice.\n");
        }
    } while (choice != 7);

    free_all();
    printf("\nGoodbye!\n");
    return 0;
}
