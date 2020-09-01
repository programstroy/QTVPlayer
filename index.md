## Добро пожаловать на страницу QTVPlayer

Смотрите IP-телевидение вашего интернет-провайдера или ТВ из любого другого интернет-источника на телефоне, планшете или компьютере под управлением Windows/Linux.

Возможности приложения:

- Поддержка плейлистов m3u и собственного формата [xml](https://github.com/programstroy/QTVPlayer-release/tree/master/playlist)

- Отображение каналов в виде бегущей строки

- Удаление дублируемых или не работающих каналов

- Автоматическая поддержка телепрограммы

- Отсутствие рекламы :)

Вы можете использовать исходный код по своему усмотрению, придерживаясь правил лицензии [GNU LESSER GENERAL PUBLIC LICENSE Version 3](https://www.gnu.org/licenses/lgpl-3.0.ru.html)

You can use the [editor on GitHub](https://github.com/programstroy/QTVPlayer-release/edit/gh-pages/index.md) to maintain and preview the content for your website in Markdown files.

Whenever you commit to this repository, GitHub Pages will run [Jekyll](https://jekyllrb.com/) to rebuild the pages in your site, from the content in your Markdown files.

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

Уже готовый плейлист можно скачать [отсюда](https://github.com/programstroy/QTVPlayer-release/tree/master/playlist)

 
Markdown is a lightweight and easy-to-use syntax for styling your writing. It includes conventions for

```markdown
Syntax highlighted code block

# Header 1
## Header 2
### Header 3

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```

For more details see [GitHub Flavored Markdown](https://guides.github.com/features/mastering-markdown/).

### Jekyll Themes

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/programstroy/QTVPlayer-release/settings). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://docs.github.com/categories/github-pages-basics/) or [contact support](https://github.com/contact) and we’ll help you sort it out.
