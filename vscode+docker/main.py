# -*- encoding:utf-8 -*-
import datetime
from flask import Flask, request, jsonify, make_response
import requests, re, os, random
import json
import api
from WXBizMsgCrypt import WXBizMsgCrypt, XMLParse, ET
from urllib.parse import unquote

app = Flask(__name__)
token = api.get_token()
my_crypt = WXBizMsgCrypt(api.receive_token, api.AESKey, api.corpid)


@app.route('/', methods=["GET"])
def check():
    if request.method == 'GET':
        msg_signature = request.args.get('msg_signature')
        timestamp = request.args.get('timestamp')
        nonce = request.args.get('nonce')
        echostr = request.args.get('echostr')
        ret, content = my_crypt.VerifyURL(msg_signature, timestamp, nonce, echostr)
        response = make_response(content)

        return response


@app.route('/', methods=["POST"])
def receive():
    if request.method == 'POST':
        msg_signature = request.args.get('msg_signature')
        timestamp = request.args.get('timestamp')
        nonce = request.args.get('nonce')
        ret, xml_content = my_crypt.DecryptMsg(request.get_data(), msg_signature, timestamp, nonce)
        content = ET.fromstring(xml_content).find("Content")
        user = ET.fromstring(xml_content).find("FromUserName")
        print(xml_content)
        response = make_response(jsonify({'message': 'OK'}, 200))

        api.send_message_all((
                "服务端于" + datetime.datetime.strftime(datetime.datetime.now(),
                                                    "%y-%m-%d %H:%M:%S") + "收到来自用户：" + user.text + "的消息：\n" + content.text),
            token)

        return response


if __name__ == "__main__":
    app.config['SERVER_NAME'] = 'namotechnology.cn:8000'
    app.run('0.0.0.0', debug=True, port=8000, ssl_context=("namotechnology.cn.pem", 'namotechnology.cn.key'))