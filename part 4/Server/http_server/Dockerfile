FROM python:3.8



RUN pip3 config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple
RUN pip3 install flask redis requests pyyaml pycrypto

COPY . .

CMD python3 main.py