#include "telegid.h"

void TELEGID::setModel(QVector<TELEGID::TV_SHOW_LIST> data, QString id){
    QStringList model = QStringList();
    foreach(auto rec, data){
        if (rec.ch_id == id){
            foreach(auto show, rec.ch_show){
                model.append(show.start.append("  ").append(show.event));
            }
        }
    }
    if (model.isEmpty()) model << "данные отсутствуют";
    emit dataUpdated(model);
}

void TELEGID::setChannel(QString id){
    //получаем json данные с сервера mail.ru
    QString url("https://tv.mail.ru/ajax/index/?period=now&channel_type=all&appearance=grid&ex=713&ex=714&ex=715&ex=717&ex=726&ex=729&ex=732&ex=734&ex=736&ex=739&ex=742&ex=743&ex=744&ex=745&ex=761&ex=763&ex=766&ex=769&ex=773&ex=775&ex=781&ex=782&ex=786&ex=787&ex=796&ex=800&ex=801&ex=806&ex=808&ex=810&ex=814&ex=822&ex=832&ex=833&ex=834&ex=835&ex=838&ex=843&ex=850&ex=853&ex=864&ex=868&ex=873&ex=888&ex=889&ex=896&ex=901&ex=904&ex=905&ex=907&ex=911&ex=919&ex=921&ex=924&ex=927&ex=927&ex=929&ex=933&ex=942&ex=943&ex=943&ex=945&ex=948&ex=953&ex=963&ex=968&ex=974&ex=975&ex=980&ex=981&ex=986&ex=994&ex=1002&ex=1003&ex=1004&ex=1007&ex=1008&ex=1010&ex=1014&ex=1014&ex=1019&ex=1023&ex=1023&ex=1027&ex=1038&ex=1042&ex=1049&ex=1050&ex=1051&ex=1057&ex=1063&ex=1064&ex=1066&ex=1070&ex=1075&ex=1083&ex=1085&ex=1091&ex=1092&ex=1094&ex=1096&ex=1096&ex=1097&ex=1101&ex=1103&ex=1104&ex=1111&ex=1112&ex=1116&ex=1122&ex=1126&ex=1127&ex=1128&ex=1129&ex=1134&ex=1136&ex=1141&ex=1143&ex=1144&ex=1148&ex=1156&ex=1159&ex=1162&ex=1169&ex=1174&ex=1179&ex=1179&ex=1182&ex=1185&ex=1193&ex=1195&ex=1197&ex=1201&ex=1204&ex=1219&ex=1229&ex=1234&ex=1241&ex=1243&ex=1244&ex=1249&ex=1250&ex=1252&ex=1255&ex=1255&ex=1257&ex=1258&ex=1259&ex=1262&ex=1263&ex=1266&ex=1269&ex=1271&ex=1282&ex=1296&ex=1300&ex=1302&ex=1307&ex=1309&ex=1319&ex=1324&ex=1326&ex=1333&ex=1334&ex=1340&ex=1343&ex=1346&ex=1352&ex=1353&ex=1354&ex=1356&ex=1362&ex=1366&ex=1367&ex=1378&ex=1380&ex=1381&ex=1384&ex=1385&ex=1395&ex=1396&ex=1397&ex=1401&ex=1404&ex=1405&ex=1408&ex=1420&ex=1422&ex=1429&ex=1429&ex=1433&ex=1436&ex=1449&ex=1454&ex=1470&ex=1474&ex=1477&ex=1479&ex=1498&ex=1503&ex=1507&ex=1511&ex=1516&ex=1521&ex=1524&ex=1528&ex=1542&ex=1552&ex=1557&ex=1559&ex=1561&ex=1566&ex=1567&ex=1570&ex=1572&ex=1574&ex=1576&ex=1579&ex=1590&ex=1598&ex=1603&ex=1610&ex=1612&ex=1617&ex=1618&ex=1619&ex=1622&ex=1624&ex=1624&ex=1628&ex=1633&ex=1633&ex=1637&ex=1637&ex=1638&ex=1638&ex=1651&ex=1652&ex=1653&ex=1658&ex=1660&ex=1666&ex=1669&ex=1670&ex=1671&ex=1683&ex=1684&ex=1693&ex=1700&ex=1702&ex=1707&ex=1714&ex=1714&ex=1716&ex=1717&ex=1717&ex=1718&ex=1721&ex=1723&ex=1727&ex=1732&ex=1732&ex=1739&ex=1741&ex=1744&ex=1754&ex=1754&ex=1759&ex=1778&ex=1780&ex=1781&ex=1784&ex=1786&ex=1787&ex=1794&ex=1798&ex=1799&ex=1800&ex=1801&ex=1806&ex=1809&ex=1810&ex=1811&ex=1813&ex=1817&ex=1818&ex=1821&ex=1825&ex=1827&ex=1829&ex=1830&ex=1831&ex=1832&ex=1834&ex=1835&ex=1836&ex=1840&ex=1840&ex=1851&ex=1854&ex=1871&ex=1872&ex=1872&ex=1882&ex=1882&ex=1884&ex=1894&ex=1921&ex=1921&ex=1926&ex=1944&ex=1956&ex=1961&ex=1968&ex=1973&ex=1991&ex=1993&ex=2006&ex=2007&ex=2008&ex=2011&ex=2015&ex=2024&ex=2035&ex=2042&ex=2043&ex=2043&ex=2044&ex=2048&ex=2060&ex=2068&ex=2090&ex=2097&ex=2111&ex=2113&ex=2115&ex=2116&ex=2121&ex=2122&ex=2123&ex=2124&ex=2135&ex=2136&ex=2137&ex=2150&ex=2153&ex=2154&ex=2161&ex=2166&ex=2168&ex=2173&ex=2174&ex=2175&ex=2179&ex=2180&ex=2181&ex=2186&ex=2194&ex=2195&ex=2197&ex=2198&ex=2199&ex=2200&ex=2202&ex=2204&ex=2206&ex=2207&ex=2212&ex=2214&ex=2215&ex=2216&ex=2217&ex=2224&ex=2227&ex=2232&ex=2234&ex=2235&ex=2237&ex=2243&ex=2244&ex=2246&ex=2252&ex=2258&ex=2259&ex=2261&ex=2262&ex=2263&ex=2264&ex=2266&ex=2269&ex=2273&ex=2274&ex=2276&ex=2277&ex=2279&ex=2280&ex=2281&ex=2285&ex=2287&ex=2288&ex=2290&ex=2291&ex=2293&ex=2294&ex=2295&ex=2296&ex=2298&ex=2300&ex=2301&ex=2303&ex=2304&ex=2305&ex=2306&ex=2309&ex=2310&ex=2311&ex=2317&ex=2320&ex=2321&ex=2324&ex=2325&ex=2326&ex=2338&ex=2339&ex=2341&ex=2348&ex=2349&ex=2351&ex=2353&ex=2355&ex=2356&ex=2367&ex=2368&ex=2369&ex=2383&ex=2384&ex=2386&ex=2396&ex=2399&ex=2401&ex=2404&ex=2407&ex=2411&ex=2416&ex=2420&ex=2423&ex=2424&ex=2425&ex=2426&ex=2427&ex=2437&ex=2445&ex=2446&ex=2447&ex=2448&ex=2450&ex=2451&ex=2452&ex=2456&ex=2457&ex=2458&ex=2463&ex=2465&ex=2468&ex=2470&ex=2486&ex=2487&ex=2507&ex=2519&ex=2580&ex=2613&ex=2615&ex=2616&ex=2622&ex=2669&ex=2672&ex=2673&ex=2673&ex=2674&ex=2675&ex=2676&ex=2677&ex=2678&ex=2680&ex=2681&ex=2682&ex=2693&ex=2698&ex=2701&ex=2702&ex=2704&ex=2705&ex=2706&ex=2711&ex=2716&ex=2717&ex=2721&ex=2724&ex=2726&ex=2727&ex=2728&ex=2729&ex=2731&ex=2735&ex=2736&ex=2737&ex=2739&ex=2740&ex=2741&ex=2742&ex=2743&ex=2744&ex=2745&ex=2746&ex=2747&ex=2748&ex=2749&ex=2750&ex=2751&ex=2753&ex=2755&ex=2756&ex=2771&ex=2772&ex=2775&ex=2777&ex=2794&ex=2795&ex=2797&ex=2798&ex=2802&ex=2805&ex=2806&ex=2807&ex=2808&ex=2810&ex=2811&ex=2820&ex=2823&ex=2832&ex=2844&ex=2854&ex=2856&ex=2859&ex=2860&ex=2863&ex=2865&ex=2868&ex=2869&ex=2871&ex=2873&ex=2874&ex=2875&ex=2876&ex=2881&ex=2882&ex=2885&ex=2885&ex=2893&ex=2894&ex=2916&ex=2919&ex=2922&ex=2976&ex=2977&ex=2979&ex=2981&ex=2983&ex=2987&ex=2994&ex=2994&ex=3011&ex=3032&ex=3108&ex=3111&ex=3117&ex=3118&ex=3123&ex=3137&ex=3138&ex=3139&ex=3140&ex=3141&ex=3142&ex=3153");
    url.replace("&ex=" + id,"");
    QNetworkProxyFactory::setUseSystemConfiguration(true);
    QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");
    QNetworkAccessManager manager;
    QEventLoop loop;
    QObject::connect(&manager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    loop.processEvents(QEventLoop::ExcludeUserInputEvents,5000);
    QSharedPointer<QNetworkReply> reply(manager.get(QNetworkRequest(QUrl(url))));
    loop.exec();
    manager.disconnect();

    if (reply.data()->error() == QNetworkReply::NoError) {

        //переводим json данные (jsonData) tv.mail.ru в формат TV_SHOW_LIST (tvData)
        auto jsonData = toJson(static_cast<QString>(reply.data()->readAll()).toUtf8());
        QVector<TV_SHOW_LIST> tvData;

        //читаем элементы секции "программа передач"
        foreach (auto task, jsonData["schedule"].toArray()) {

            //данные по каналу: id и наименование
            auto channel = task["channel"].toObject();
            TV_SHOW_LIST tvList(channel["id"].toString(),channel["name"].toString());

            //данные по последним передачам
            foreach (auto event, task["event"].toArray())\
                tvList.ch_show.append(TV_SHOW(event["start"].toString(),event["name"].toString()));
            tvData.append(tvList);
        }
        setModel(tvData,id);
    }
    else{
        QStringList model = QStringList();
        model << reply.data()->errorString().split("\n");
        emit dataUpdated(model);
    }
}

