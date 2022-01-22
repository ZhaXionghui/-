FROM python:3.8

COPY . .

RUN pip3 config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple
RUN pip3 install -r requirements.txt

CMD python3 main.py