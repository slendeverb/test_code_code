import torch

print(torch.__version__,torch.cuda.is_available())
print(torch.cuda.current_device(),torch.cuda.get_device_name())