/** @file Station.h
 *  @brief Contains the Station class declaration.
 *  @author -
 *  @bug No known bugs.
 */

#ifndef PROJ1_DA_2022_2023_STATION_H
#define PROJ1_DA_2022_2023_STATION_H

#include "string"

/** @brief Station class to represent a station.
 *
 */
class   Station {

    //! @brief Holds the station id.
    const int id;

    //! @brief Holds the station name.
    const std::string name;

    //! @brief Holds the station district.
    const std::string district;

    //! @brief Holds the station municipality.
    const std::string municipality;

    //! @brief Holds the station township.
    const std::string township;

    //! @brief Holds the station line.
    const std::string line;

public:

    /** Creates a new station with an id, a name, a district, a municipality, a township and a line.
     *
     * @param id of const int type.
     * @param name of const std::string type, by reference.
     * @param district of const std::string type, by reference.
     * @param municipality of const std::string type, by reference.
     * @param township of const std::string type, by reference.
     * @param line of const std::string type, by reference.
     */
    Station(const int id, const std::string &name, const std::string &district,
            const std::string &municipality, const std::string &township, const std::string &line);

    /** @brief Represents the station id.
     *
     * @return Id,by reference.
     */
    const int &getId() const;

    /** @brief Represents the station name.
     *
     * @return Name,by reference.
     */
    const std::string &getName() const;

    /** @brief Represents the station district.
     *
     * @return District,by reference.
     */
    const std::string &getDistrict() const;

    /** @brief Represents the station municipality.
     *
     * @return Municipality,by reference.
     */
    const std::string &getMunicipality() const;

    /** @brief Represents the station township.
     *
     * @return Township,by reference.
     */
    const std::string &getTownship() const;

    /** @brief Represents the station line.
     *
     * @return Line,by reference.
     */
    const std::string &getLine() const;
};


#endif //PROJ1_DA_2022_2023_STATION_H
