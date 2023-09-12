# exp No.0
# CUDA_VISIBLE_DEVICES=0,1 python regbug_reducing.py --dataset emnist --dataset_size 1.0 --ensemble 'scaling_unlabel' \
#    --old_model mnistlenet --oldmodel_path ./save/models/mnistlenet_mnist_1.0_lr_0.0005_decay_0.0_trial_1/mnistlenet_dataset_1.0_best.pth \
#    --new_model mnistlenet --newmodel_path ./save/models/mnistlenet_emnist_0.1_lr_0.0005_decay_0.0_trial_1/mnistlenet_dataset_0.1_best.pth

# exp No.1
# CUDA_VISIBLE_DEVICES=4,5 python regbug_reducing.py --dataset stl10 --dataset_size 1.0 --ensemble 'scaling_unlabel' \
#    --old_model alexnet32 --oldmodel_path ./save/models/alexnet32_stl10_1.0_lr_0.0005_decay_0.0_trial_1/alexnet32_dataset_1.0_best.pth \
#    --new_model vgg16 --newmodel_path ./save/models/vgg16_stl10_1.0_lr_0.05_decay_0.0005_trial_1/vgg16_dataset_1.0_best.pth

# exp No.2
# CUDA_VISIBLE_DEVICES=0,1 python regbug_reducing.py --dataset stl10 --dataset_size 1.0 --ensemble 'scaling_unlabel' \
#    --old_model vgg8 --oldmodel_path ./save/models/vgg8_cifar10_1.0_lr_0.05_decay_0.0_trial_1/vgg8_dataset_1.0_best.pth \
#    --new_model resnet56 --newmodel_path ./save/models/resnet56_stl10_1.0_lr_0.05_decay_0.0005_trial_1/resnet56_dataset_1.0_best.pth

# exp No.3
# CUDA_VISIBLE_DEVICES=9,10 python regbug_reducing.py --dataset cifar100 --dataset_size 1.0 --ensemble 'scaling_unlabel' \
#    --old_model densenet40 --oldmodel_path ./save/models/densenet40_cifar100_0.25_lr_0.05_decay_0.0_trial_1/densenet40_dataset_0.25_best.pth \
#    --new_model resnet110 --newmodel_path ./save/models/resnet110_cifar100_1.0_lr_0.05_decay_0.0005_trial_1/resnet110_dataset_1.0_best.pth

# exp No.4
# CUDA_VISIBLE_DEVICES=9,10 python regbug_reducing.py --dataset imageclef --category 'p' --dataset_size 1.0 --ensemble 'scaling_unlabel' \
#    --old_model ResNet50 --oldmodel_path ./save/best_resnet_c.pth --is_model_old 0 --del_module_old 0 \
#    --new_model densenet169 --newmodel_path ./save/models/densenet169_imageclef_1.0_lr_0.001_decay_0.0_trial_1/densenet169_dataset_1.0_best.pth \

# exp No.5
# CUDA_VISIBLE_DEVICES=2,3 python regbug_reducing.py --dataset objectnet --dataset_size 1.0 --ensemble 'scaling_unlabel' \
   # --old_model ResNet18 --oldmodel_path ./save/resnet18-f37072fd.pth --is_model_old 0 --del_module_old 0 \
   # --new_model wrn --newmodel_path ./save/wide_resnet101_2-32ee1156.pth --is_model_new 0 --del_module_new 0

# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# for additional exp
# CUDA_VISIBLE_DEVICES=0,1 python regbug_reducing.py --dataset cifar100 --dataset_size 1.0 --ensemble 'scaling_unlabel' \
   # --old_model cifarresnet34 --oldmodel_path ./save/models/cifarresnet34_cifar100_1.0_lr_0.05_decay_0.0005_trial_1/cifarresnet34_dataset_1.0_best.pth \
   # --new_model cifarresnet50 --newmodel_path /data/share/zmr/regression_bug/save/student_model/cifarresnet34_cifarresnet50_cifar100_1.0_kd_trial_0/cifarresnet50_best.pth

