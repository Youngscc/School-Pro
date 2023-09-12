from .alexnet import alexnet
from .alexnet32x32 import alexnet32x32
from .MnistLenet import mnistlenet
from .vanilla_rnn import Net
from .resnet import resnet8, resnet14, resnet20, resnet32, resnet44, resnet56, resnet110, resnet8x4, resnet32x4
from .resnetv2 import ResNet18, ResNet34, ResNet50, ResNet101, ResNet152
import torchvision.models as models
from .wrn import wide_resnet101_2
from .vgg import vgg19_bn, vgg16_bn, vgg13_bn, vgg11_bn, vgg8_bn
# from .mobilenetv2 import mobile_half
# from .ShuffleNetv1 import ShuffleV1
# from .ShuffleNetv2 import ShuffleV2
from .densenet import densenet100, densenet40
from .densenetv2 import densenet121, densenet161, densenet169, densenet201
from .mobilenetv3 import mobilenetv3_large, mobilenetv3_small
from .inceptionv3 import Inception3
from .CifarResNet import cifarresnet18, cifarresnet34, cifarresnet50, cifarresnet101, cifarresnet152
# from .resnext import resnext101, resnext29
from .ensemble_model import ensemble_model

model_dict = {
    'prealexnet': models.alexnet,
    'alexnet': alexnet,

    'alexnet32': alexnet32x32,
    'mnistlenet': mnistlenet, 

    'rnn': Net,

    'resnet8': resnet8,
    'resnet14': resnet14,
    'resnet20': resnet20,
    'resnet32': resnet32,
    'resnet44': resnet44,
    'resnet56': resnet56,
    'resnet110': resnet110,
    'resnet8x4': resnet8x4,
    'resnet32x4': resnet32x4,
    'ResNet18': ResNet18,
    'ResNet34': ResNet34,
    'ResNet50': ResNet50,
    'ResNet101': ResNet101,
    'ResNet152': ResNet152,

    'preResNet18': models.resnet18,
    'preResNet50': models.resnet50,
    'preResNet152': models.resnet152,

    'vgg8': vgg8_bn,
    'vgg11': vgg11_bn,
    'vgg13': vgg13_bn,
    'vgg16': vgg16_bn,
    'vgg19': vgg19_bn,
    'prevgg11': models.vgg11, 
    
    # 'MobileNetV2': mobile_half,
    'ShuffleV1': models.shufflenet_v2_x0_5,
    # 'ShuffleV2': ShuffleV2,

    'densenet100': densenet100,
    'densenet40': densenet40,
    'densenet121': densenet121,
    'densenet161': densenet161,
    'densenet169': densenet169,
    'densenet201': densenet201,

    'inceptionv3': Inception3,
    'preinceptionv3': models.inception_v3,

    'predensenet121': models.densenet121,
    'predensenet169': models.densenet169,
    'predensenet201': models.densenet201,

    'efficientnet': models.efficientnet_b7,
    'preefficientnet': models.efficientnet_b7,

    'MobileNetLarge': mobilenetv3_large,
    'MobileNetSmall': mobilenetv3_small,
    'preMobileNetLarge': models.mobilenet_v3_large,
    'preMobileNetSmall': models.mobilenet_v3_small,   

    'wrn': wide_resnet101_2, # models.wide_resnet101_2,  

    'cifarresnet18': cifarresnet18, 
    'cifarresnet34': cifarresnet34,     
    'cifarresnet50': cifarresnet50, 
    'cifarresnet101': cifarresnet101, 
    'cifarresnet152': cifarresnet152,

    # 'resnext101': resnext101,
    # 'resnext29': resnext29,
    'ensemble_model': ensemble_model
}
