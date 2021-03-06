#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp = fopen("orig.txt", "r");
    FILE *output = fopen("output.txt", "w");
    /*original*/
    if (!fp) {
        printf("ERROR opening input file orig.txt\n");
        exit(0);
    }
    int i = 0;
    char append[50], find[50];
    double orig_sum_a = 0.0, orig_sum_f = 0.0, orig_a, orig_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %lf %lf\n", append, find,&orig_a, &orig_f);
        orig_sum_a += orig_a;
        orig_sum_f += orig_f;
    }
    fclose(fp);
    /*optimal*/
    fp = fopen("opt.txt", "r");
    if (!fp) {
        fp = fopen("orig.txt", "r");
        if (!fp) {
            printf("ERROR opening input file opt.txt\n");
            exit(0);
        }
    }
    double opt_sum_a = 0.0, opt_sum_f = 0.0, opt_a, opt_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %lf %lf\n", append, find,&opt_a, &opt_f);
        opt_sum_a += opt_a;
        opt_sum_f += opt_f;
    }

    fclose(fp);
    /*hash*/
    fp = fopen("hash.txt", "r");
    if (!fp) {
        fp = fopen("orig.txt", "r");
        if (!fp) {
            printf("ERROR opening input file opt.txt\n");
            exit(0);
        }
    }
    double hash_sum_a = 0.0, hash_sum_f = 0.0, hash_a, hash_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %lf %lf\n", append, find,&hash_a, &hash_f);
        hash_sum_a += hash_a;
        hash_sum_f += hash_f;
    }
    fclose(fp);
    /*Memory Pool*/
    fp = fopen("memory.txt", "r");
    if (!fp) {
        fp = fopen("orig.txt", "r");
        if (!fp) {
            printf("ERROR opening input file opt.txt\n");
            exit(0);
        }
    }
    double mem_sum_a = 0.0, mem_sum_f = 0.0, mem_a, mem_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %lf %lf\n", append, find,&mem_a, &mem_f);
        mem_sum_a += mem_a;
        mem_sum_f += mem_f;
    }
    fclose(fp);

    /*mmap*/
    fp = fopen("mmap.txt", "r");
    if (!fp) {
        fp = fopen("orig.txt", "r");
        if (!fp) {
            printf("ERROR opening input file opt.txt\n");
            exit(0);
        }
    }
    double mmap_sum_a = 0.0, mmap_sum_f = 0.0, mmap_a, mmap_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %lf %lf\n", append, find,&mmap_a, &mmap_f);
        mmap_sum_a += mmap_a;
        mmap_sum_f += mmap_f;
    }
    fclose(fp);

    /*thread*/
    fp = fopen("thread.txt", "r");
    if (!fp) {
        fp = fopen("orig.txt", "r");
        if (!fp) {
            printf("ERROR opening input file opt.txt\n");
            exit(0);
        }
    }
    double thr_sum_a = 0.0, thr_sum_f = 0.0, thr_a, thr_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %lf %lf\n", append, find,&thr_a, &thr_f);
        thr_sum_a += thr_a;
        thr_sum_f += thr_f;
    }

    fprintf(output, "append() %lf %lf %lf %f %f %f\n",orig_sum_a / 100.0, opt_sum_a / 100.0, hash_sum_a / 100.0, mem_sum_a / 100.0, mmap_sum_a / 100.0,  thr_sum_a / 100.0);
    fprintf(output, "findName() %lf %lf %lf %f %f %f", orig_sum_f / 100.0, opt_sum_f / 100.0, hash_sum_f / 100.0, mem_sum_f / 100.0, mmap_sum_f / 100.0,  thr_sum_f / 100.0);
    fclose(output);
    fclose(fp);
    return 0;
}
