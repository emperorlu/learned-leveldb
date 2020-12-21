#!/bin/bash

cd ../build

# Datasets (file)
./read_cold -f /mnt/db/dataset/amazon_reviews.txt -k 16 -v 64 -d /mnt/ssd/db_ar -m 7 -u -n 10000 -i 5 $* --change_level_load > ../evaluation/ar_llsm.txt
./read_cold -f /mnt/db/dataset/amazon_reviews.txt -k 16 -v 64 -d /mnt/ssd/db_ar -m 7 -u -n 10000 -i 5 $* --change_level_load > ../evaluation/ar_llsm.txt
./read_cold -f /mnt/db/dataset/amazon_reviews.txt -k 16 -v 64 -d /mnt/ssd/db_ar -m 8 -u -n 10000 -i 5 $* --change_level_load > ../evaluation/ar_baseline.txt
sync; echo 3 | sudo tee /proc/sys/vm/drop_caches

# Datasets (level)
./read_cold -f /mnt/db/dataset/amazon_reviews.txt -k 16 -v 64 -d /mnt/ssd/db_ar -m 7 -u -n 10000 -i 5 $* > ../evaluation/ar_llsm_level.txt
./read_cold -f /mnt/db/dataset/amazon_reviews.txt -k 16 -v 64 -d /mnt/ssd/db_ar -m 7 -u -n 10000 -i 5 $* > ../evaluation/ar_llsm_level.txt
sync; echo 3 | sudo tee /proc/sys/vm/drop_caches

cd ..
python3 scripts/collect_results.py 1 > evaluation/expr_dataset.txt
cat evaluation/expr_dataset.txt
