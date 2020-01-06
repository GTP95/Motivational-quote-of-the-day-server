useradd --system --create-home qotd
cp mqotd /usr/bin/
cp quotes.txt /home/qotd
cp mqotd.service /etc/systemd/system/
systemctl start mqotd.service
systemctl enable mqotd.service