#!/bin/bash
TELEGRAM_BOT_TOKEN="7440305009:AAF70i_XO8nfzS2DUduyB_XgH1Z4DBsEEME"
TELEGRAM_USER_ID="376951707"
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="Project:+$CI_PROJECT_NAME%0AJob name: $CI_JOB_NAME%0AStatus:+$CI_JOB_STATUS"

curl -s -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null