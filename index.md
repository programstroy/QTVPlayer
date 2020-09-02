

Смотрите IP-телевидение вашего интернет-провайдера или ТВ из любого другого интернет-источника на телефоне, планшете или компьютере под управлением Windows/Linux.

Возможности приложения:

- Поддержка плейлистов m3u и собственного формата [xml](https://github.com/programstroy/QTVPlayer-release/tree/master/playlist)

- Отображение каналов в виде бегущей строки

- Удаление дублируемых или не работающих каналов

- Автоматическая поддержка телепрограммы

- Отсутствие рекламы :)

При использовании исходного кода следует придерживаться лицензии [GNU LESSER GENERAL PUBLIC LICENSE Version 3](https://www.gnu.org/licenses/lgpl-3.0.ru.html)

### Схема управления плеером
![Branching](https://raw.githubusercontent.com/programstroy/QTVPlayer-release/gh-pages/screenshot.png)

### Структура формата плейлиста ChannelsList.xml
```markdown
<ListElement>
  <channel_id>850</channel_id>
  <caption>Первый канал</caption>
  <source>http://internet_path/streaming_playlist.m3u8</source>
  <cover>qrc:/covers/850.png</cover>
</ListElement>
```  
**channel_id** - фиксированный номер канала (не менять!!!)

**caption** - наименование канала

**source** - ссылка m3u8 для просмотра канала (из любого плейлиста IPTV M3U)

**cover** - логотип (qrc:/covers/NNN.png, где NNN - **channel_id**)

Уже **готовый плейлист** можно скачать [**здесь**](https://github.com/programstroy/QTVPlayer-release/tree/master/playlist)

### Остались вопросы?

Разбирайтесь сами, или пишите на почту yandex.ru
