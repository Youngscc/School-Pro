# exp addition
# CUDA_VISIBLE_DEVICES=6 python train_model.py --dataset stl10 --model alexnet32 --dataset_size 1.0 --learning_algorithm 'adam' --epochs 600 --learning_rate 5e-4 --trial 1 
# CUDA_VISIBLE_DEVICES=7 python train_model.py --dataset stl10 --dataset_size 1.0 --model resnet56 --epochs 600 --trial 1

# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# for comparison exp
# CUDA_VISIBLE_DEVICES=0,1 python compare.py --dataset stl10 --dataset_size 1.0 --ensemble 'compare' --T1 0.2 --T2 10.0 \
   # --old_model alexnet32 --oldmodel_path ./save/models/alexnet32_stl10_1.0_lr_0.0005_decay_0.0_trial_1/alexnet32_dataset_1.0_best.pth \
   # --new_model resnet56 --newmodel_path ./save/models/resnet56_stl10_1.0_lr_0.05_decay_0.0_trial_1/resnet56_dataset_1.0_best.pth \

CUDA_VISIBLE_DEVICES=0,1 python compare.py --dataset stl10 --dataset_size 1.0 --ensemble 'compare' --T1 200.0 --T2 1.0 \
   --old_model alexnet32 --oldmodel_path ./save/models/alexnet32_stl10_1.0_lr_0.0005_decay_0.0_trial_1/alexnet32_dataset_1.0_best.pth \
   --new_model resnet56 --newmodel_path ./save/models/resnet56_stl10_1.0_lr_0.05_decay_0.0_trial_1/resnet56_dataset_1.0_best.pth \
