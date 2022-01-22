sudo docker kill helpdesk
sudo docker rm helpdesk
sudo docker run -p 8000:8000 --name helpdesk username/helpdesk
