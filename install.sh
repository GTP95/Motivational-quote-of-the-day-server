useradd --system --create-home qotd
cp build/mqotd /home/qotd
cp quotes.txt /home/qotd
chown qotd /home/qotd/mqotd
chown qotd /home/qotd/quotes.txt
cp mqotd.service /etc/systemd/system/
systemctl start mqotd.service
systemctl enable mqotd.service