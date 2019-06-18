type action =
  | Update(string);
type state = {text: string};
module Styles = {
  open Css;
  let input =
    style([
      border(px(1), solid, black),
      borderRadius(px(5)),
      lineHeight(rem(1.0)),
      maxWidth(pct(100.0)),
      fontSize(rem(1.5)),
      padding4(rem(0.75), rem(0.0), rem(0.75), rem(1.25)),
    ]);
};

[@react.component]
let make = (~update, ~startText) => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch ((action: action)) {
        | Update(text) => {text: text}
        },
      {text: ""},
    );
  <div>
    <input
      className=Styles.input
      type_="text"
      placeholder=startText
      onChange={e => {
        let text = ReactEvent.Form.target(e)##value;
        dispatch(Update(text));
        update(text);
      }}
    />
  </div>;
};
