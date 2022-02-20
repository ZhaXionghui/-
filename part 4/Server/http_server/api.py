# -*- encoding:utf-8 -*-
import requests
import yaml

# 以utf-8编码打开并阅读config.yaml文件
config_file = open("config.yaml", "r", encoding="utf-8")

config = yaml.load(config_file.read(), Loader=yaml.FullLoader)

# 关闭config.yaml文件
config_file.close()

# 设置相关变量
corpid = config["corpid"]
corpsecret = config["corpsecret"]
receive_token = config["receive_token"]
AESKey = config["AESKey"]

# 获取并返回token地址
def get_token():
    res = requests.get(
        "https://qyapi.weixin.qq.com/cgi-bin/gettoken?corpid=%s" % corpid + "&corpsecret=%s" % corpsecret)
    return res.json()['access_token']

'''
设置send_message_all发送消息

将消息发送给应用指定的用户
message：String //要发送的消息
token：String //企业微信api获取的token

返回发送结果
'''
def send_message_all(message, token):
    request_body = """{
       "touser" : "@all",
       "msgtype" : "text",
       "agentid" : 1000003,
       "text" : {
           "content" : "%s""" % message + """"
    },
    "safe": 0,
    "enable_id_trans": 0,
    "enable_duplicate_check": 0,
    "duplicate_check_interval": 1800
    
    }"""
    res = requests.post('https://qyapi.weixin.qq.com/cgi-bin/message/send?access_token=%s' % token,
                        data=request_body.encode('utf-8'))
                       
    print(res)
    return res