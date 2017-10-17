#include "offermodel.h"

OfferModel::OfferModel(const std::list<OfferInfo> &offers, QObject *parent) : QAbstractTableModel(parent)
{
    this->offers = QList<OfferInfo>::fromStdList(offers);
    offersView = this->offers;
    listHead << tr("Price") << tr("Short Info") << tr("Min Amount") << tr("More Details");
}

OfferModel::~OfferModel()
{

}

void OfferModel::setFilterCountryIso(const std::string &iso)
{
    countryIso = iso;
    filterOffers();
}

void OfferModel::setFilterCurrencyIso(const std::string &iso)
{
    currencyIso = iso;
    filterOffers();
}

void OfferModel::setFilterPaymentMethod(const uint8_t &payment)
{
    paymentMethod = payment;
    filterOffers();
}

OfferInfo OfferModel::offerInfo(const int &row)
{
    if (row < offersView.size()) {
        return offersView[row];
    }

    return OfferInfo();
}

QVariant OfferModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= offersView.size()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case 0:
            return static_cast<quint64>(offersView[index.row()].price);
        case 1:
            return QString::fromStdString(offersView[index.row()].shortInfo);
        case 2:
            return static_cast<quint64>(offersView[index.row()].minAmount);
        case 3:
            return tr("More Details");
        default:
            break;
        }
    }

    return QVariant();
}

int OfferModel::rowCount(const QModelIndex &parent) const
{
    return offersView.size();
}

int OfferModel::columnCount(const QModelIndex &parent) const
{
    return listHead.size();
}

QVariant OfferModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        return listHead.at(section);
    }

    return QVariant();
}

Qt::ItemFlags OfferModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::ItemIsEnabled;
    }

    return QAbstractItemModel::flags(index);
}

void OfferModel::sort(int column, Qt::SortOrder order)
{
    if (order == Qt::AscendingOrder) {
        switch (column) {
        case 0:
            qSort(offersView.begin(), offersView.end(), [](OfferInfo& a, OfferInfo& b) { return a.price < b.price; } );
            break;
        case 1:
            qSort(offersView.begin(), offersView.end(), [](OfferInfo& a, OfferInfo& b) { return a.shortInfo < b.shortInfo; } );
            break;
        case 2:
            qSort(offersView.begin(), offersView.end(), [](OfferInfo& a, OfferInfo& b) { return a.minAmount < b.minAmount; } );
            break;
        default:
            break;
        }
    } else {
        switch (column) {
        case 0:
            qSort(offersView.begin(), offersView.end(), [](OfferInfo& a, OfferInfo& b) { return a.price > b.price; } );
            break;
        case 1:
            qSort(offersView.begin(), offersView.end(), [](OfferInfo& a, OfferInfo& b) { return a.shortInfo > b.shortInfo; } );
            break;
        case 2:
            qSort(offersView.begin(), offersView.end(), [](OfferInfo& a, OfferInfo& b) { return a.minAmount > b.minAmount; } );
            break;
        default:
            break;
        }
    }

    Q_EMIT layoutChanged();
}

void OfferModel::filterOffers()
{
    offersView.clear();
    for (auto item : offers) {
        if (paymentMethod == item.paymentMethod && countryIso == item.countryIso && currencyIso == item.currencyIso) {
            offersView << item;
        }
    }

    Q_EMIT layoutChanged();
}
