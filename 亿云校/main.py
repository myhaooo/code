import m3u8

playlist = m3u8.load('https://cdn-gaoxin02.eduzhida.com/vodfiles/sharefiles/9680dfaf760a05410176d0c9694128e1/s/202411/15111804/suzb2_17486511_23364348.m3u8')  # this could also be an absolute filename
# print(playlist.segments)
# print(playlist.target_duration)
print(playlist.dumps())
# if you already have the content as string, use