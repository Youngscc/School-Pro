# exp No.1
# CUDA_VISIBLE_DEVICES=0,1 python regbug_kd.py --dataset stl10 --distill 'lm' --dataset_size 0.5 -r 1.0 -a 0.0001 --kd_T 100.0 \
   # --old_model alexnet32 --oldmodel_path ./save/models/alexnet32_stl10_0.5_lr_0.05_decay_0.0_trial_1/alexnet32_dataset_0.5_best.pth \
   # --new_model vgg19 

# CUDA_VISIBLE_DEVICES=0,1 python regbug_kd.py --dataset stl10 --distill 'kd' --dataset_size 0.5 -r 1.0 -a 0.01 --kd_T 100.0 \
   # --old_model alexnet32 --oldmodel_path ./save/models/alexnet32_stl10_0.5_lr_0.05_decay_0.0_trial_1/alexnet32_dataset_0.5_best.pth \
   # --new_model vgg19 