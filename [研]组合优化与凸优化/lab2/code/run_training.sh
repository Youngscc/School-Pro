# exp No.0
# CUDA_VISIBLE_DEVICES=6 python train_model.py --dataset mnist --model mnistlenet --learning_algorithm 'adam' --learning_rate 5e-4 --epochs 30 --dataset_size 1.0 --trial 1 
# CUDA_VISIBLE_DEVICES=7 python train_model.py --dataset emnist --model mnistlenet  --learning_algorithm 'adam' --learning_rate 5e-4 --epochs 30 --dataset_size 0.1 --trial 1 

# exp No.1 
# CUDA_VISIBLE_DEVICES=6 python train_model.py --dataset stl10 --model alexnet32 --dataset_size 1.0 --learning_algorithm 'adam' --epochs 600 --learning_rate 5e-4 --trial 1 
# CUDA_VISIBLE_DEVICES=6 python train_model.py --dataset stl10 --model vgg16 --dataset_size 1.0 --weight_decay 1e-3 --epochs 600 --trial 1

# exp No.2
python train_model.py --dataset cifar10 --dataset_size 1.0 --model vgg8 --trial 1
python train_model.py --dataset stl10 --dataset_size 1.0 --model resnet56 --epochs 600 --weight_decay 5e-4 --trial 1

# exp No.3
# CUDA_VISIBLE_DEVICES=2 python train_model.py --dataset cifar100 --dataset_size 0.25 --model densenet40 --trial 1
# CUDA_VISIBLE_DEVICES=2 python train_model.py --dataset cifar100 --dataset_size 1.0 --model resnet110 --weight_decay 5e-4 --trial 1

# exp No.4
# CUDA_VISIBLE_DEVICES=5,6,7 python train_model.py --dataset imageclef --dataset_size 1.0 --model densenet169 --category 'p' --finetune 1 --learning_rate 1e-3 --epochs 100 --trial 1

# exp No.5
# CUDA_VISIBLE_DEVICES=4,5 python train_model.py --dataset cifar100 --dataset_size 1.0 --model cifarresnet34 --weight_decay 5e-4 --trial 1
# CUDA_VISIBLE_DEVICES=6,7 python train_model.py --dataset cifar100 --dataset_size 1.0 --model cifarresnet50 --weight_decay 5e-4 --trial 1



