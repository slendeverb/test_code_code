import torch

print(torch.cuda.is_available())
print(torch.cuda.current_device(),torch.cuda.get_device_name())