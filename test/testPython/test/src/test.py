import os
from openai import OpenAI
from dotenv import load_dotenv

load_dotenv("../resources/.env")

client = OpenAI(
    # 此为默认路径，您可根据业务所在地域进行配置
    base_url=os.getenv("BASE_URL"),
    # 从环境变量中获取您的 API Key。此为默认方式，您可根据需要进行修改
    api_key=os.getenv("ARK_API_KEY"),
)

response = client.images.generate(
    # 指定您创建的方舟推理接入点 ID，此处已帮您修改为您的推理接入点 ID
    model=os.getenv("MODEL"),
    prompt="鱼眼镜头，一只猫咪的头部，画面呈现出猫咪的五官因为拍摄方式扭曲的效果。",
    size="1024x1024",
    response_format="url"        
)

print(response.data[0].url)