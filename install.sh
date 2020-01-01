useradd --system --create-home qotd
cp Motivational_quote_of_the_day_server /usr/bin/
cp mqotd.service /etc/systemd/system/
systemctl start mqotd.service
systemctl enable mqotd.service