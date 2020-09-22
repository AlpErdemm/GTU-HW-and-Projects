 %------CITY FACTS-------

 city(istanbul).
  city(izmir).
  city(antalya).
  city(erzurum).
  city(edirne).
  city(ankara).
  city(trabzon).
  city(diyarbakir).
  city(kars).
  city(gaziantep).

%------------------------
%------FLIGHTS----------------

  flight(edirne, erzurum, 5).
  flight(antalya, erzurum, 2).
  flight(antalya, izmir, 1).
  flight(antalya, diyarbakir, 5).
  flight(izmir, istanbul, 3).
  flight(ankara, izmir, 6).
  flight(istanbul, ankara, 2).
  flight(istanbul, trabzon, 3).
  flight(ankara, diyarbakir, 8).
  flight(ankara, trabzon, 6).
  flight(ankara, kars, 3).
  flight(kars, gaziantep, 3).

%------------------------------

  %direct_flight(_city1, _city2, _cost) :- (city(_city1), city(_city2), not(_city1 = _city2)), (flight(_city1, _city2, _cost) ; flight(_city2, _city1, _cost)) .
  % abstract_flight(_city1, _city2, _cost, _final) :- _final is 0, direct_flight(_city1, _city2, _final), _final is _final + _cost.
  % abstract_flight(_city1, _city2, _cost, _final) :- direct_flight(_city1, X, _cost), abstract_flight(X, _city2, _cost,  _final).

  flightV2(_city1, _city2, _cost) :- (city(_city1), city(_city2)), (flight(_city1, _city2, _cost) ; flight(_city2, _city1, _cost)).
%   flightV2:
%   city(): Checks if the given variable is a city.
%   flight(): Checks if the there is such flight exists.(Check out the documentation for
%   further information.)
%-----------------------------------------------------------------------

  route(_city1, _city2, _cost) :- flightV2(_city1, _city2, _cost).
  route(_city1, _city2, _cost) :- rec_assign_cost(_city1, _city2, _cost, []).
%   Route(): checks if there is such a flight exists.
%   rec_assign_cost(): takes the flight information in order to find all
%   of the routes and sum up the costs.(Check out the documentation for
%   further information.)
%   -----------------------------------------------------------------------
%


  rec_assign_cost(_city1, _city2, _cost, _) :- flightV2(_city1, _city2, _cost).
  rec_assign_cost(_city1, _city2, _cost, _already_assigned) :- not(member(_city1, _already_assigned)), flightV2(_city1, X, Y), rec_assign_cost(X, _city2, T, [_city1 | _already_assigned]), not(_city1 = _city2), _cost is Y + T.
%   rec_assign_cost(): takes the flight information in order to find all
%   of the routes and sum up the costs.(Check out the documentation for
%   further information.)
%-----------------------------------------------------------------------

