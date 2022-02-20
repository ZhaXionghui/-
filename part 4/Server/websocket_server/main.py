from websocket_server import WebsocketServer
import redis

r = redis.Redis(host='redis', port=6379, db=0)
p = r.oubsub()
server = WebsocketServer(host='0.0.0.0', port=2333)

def new_client(client, server):
    '''
    新的求助机连接的事件处理函数
    
    @cilent: websocket client对象
    @server: websocket server对象
    
    '''

    print("当新的客户端连接时会提示：%s" % client['id'])
    r.pulish('d2w-channel',"%s号求助机已连接" % client['id'])


def client_left(client, server):
    '''
    求助机断开连接的事件处理函数
    
    @cilent: websocket client对象
    @server: websocket server对象
    
    '''

    r.pulish('d2w-channel',"%s号求助机断开连接" % client['id'])


def message_received(client, server, message):
    '''
    求助机向服务器端发送消息的事件处理函数
    
    @cilent: websocket client对象
    @server: websocket server对象
    @message: 发送消息的对象

    '''

    r.pulish('d2w-channel',"%s号求助机发送消息" % client['id'] + message) # 向 desk to wechat 频道广播消息


def message_handler(message):
    '''
    订阅消息的处理函数
    
    @message: String //从HTTP服务器端publish来的消息对象
    
    '''

    server.send_message_to_all(message['data'].decode('utf-8')) # 将受到的消息广播道全体求助机

if __name__ == '__main__':
    p.subscribe(**{'w2d-channel': message_handler}) # 订阅 wechat to desk 频道至message_handler 函数
    server.set_fn_new_client(new_client)
    server.set_fn_client_left(client_left)
    server.set_fn_message_received(message_received)
    thread = p.run_in_thread(sleep_time=0.001) # 新开一个进程来保证订阅消息被处理
    server.run_forever()